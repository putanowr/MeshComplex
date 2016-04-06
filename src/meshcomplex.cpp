#include "meshcomplex.h"
#include "graphicsnode.h"
#include "graphicscell.h"
#include "zipper.h"

#include <vector>

#include <moab/Core.hpp>

#include <QGraphicsScene>
#include <QPointF>
#include <QRectF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>

#include <QtDebug>

MeshComplex::MeshComplex(QObject *parent) : QObject(parent) {
  myScene_ = new QGraphicsScene(-100, -100, 200, 200, this);
  myScene_->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
  //myScene_->setItemIndexMethod(QGraphicsScene::NoIndex);
  myMeshDB_ =  new (std::nothrow) moab::Core;
  setupMeshDB_();
  myGraphics_ =  new QGraphicsItemGroup;
  myScene_->addItem(myGraphics_);
}

void MeshComplex::addGraphicsNode_(moab::EntityHandle handle) {
  double coords[3];
  myMeshDB_->get_coords(&handle, 1, coords);
  GraphicsNode *n = new GraphicsNode(coords[0], coords[1]);
  myGraphics_->addToGroup(n);
  void *data[] = {n};
  auto retval = myMeshDB_->tag_set_data(myGraphicsNodesTag_, &handle, 1, data);
  checkDB_(retval);
}

void MeshComplex::addGraphicsCell_(moab::EntityHandle handle) {
  double coords[3];
  moab::Range vertices;
  myMeshDB_->get_connectivity (&handle,1, vertices);
  auto nv = vertices.size();
  std::vector<double> x(nv);
  std::vector<double> y(nv);
  myMeshDB_->get_coords(vertices, &(x[0]), &(y[0]), nullptr);
  QVector<QPointF> points;
  points.reserve(2*nv);
  for (auto && tup : zip(x,y)) {
    double px,py;
    boost::tie(px,py) = tup;
    points.push_back(QPointF(px,py));
  }
  points.push_back(QPointF(x[0], y[0]));
  GraphicsCell *c = new GraphicsCell(points);
  myGraphics_->addToGroup(c);
  //void *data[] = {n};
  //auto retval = myMeshDB_->tag_set_data(myGraphicsNodesTag_, &handle, 1, data);
  //checkDB_(retval);
  qDebug() << "Drawing cell";
}

void MeshComplex::addDualCell_(moab::EntityHandle handle) {
  std::vector<int> npts;
  std::vector<moab::DualTool::GraphicsPoint> gp;
  QVector<QPointF> points;
  myDual_->get_graphics_points(handle, npts, gp);
  for (auto && i : npts) {
    auto point = gp.at(npts[i]);
    points.push_back(QPointF(point.xyz[0],point.xyz[1]));
  }
  auto pt = gp.at(npts[0]);
  points.push_back(QPointF(pt.xyz[0], pt.xyz[1]));
  GraphicsCell *c = new GraphicsCell(points);
  myGraphics_->addToGroup(c);
  //void *data[] = {n};
  //auto retval = myMeshDB_->tag_set_data(myGraphicsNodesTag_, &handle, 1, data);
  //checkDB_(retval);
  qDebug() << "Drawing cell";
}

void MeshComplex::addNode(const QPointF &p) {
  addNode(p.x(), p.y());
}

void MeshComplex::addNode(double x, double y) {
  GraphicsNode *n = new GraphicsNode(x,y);
  myGraphics_->addToGroup(n);
}


void MeshComplex::checkDB_(moab::ErrorCode retval) {
  if (moab::MB_SUCCESS != retval) {
    qCritical() << "MOAB operation failed with message: " << myMeshDB_->get_error_string(retval).c_str();
  }
}

void MeshComplex::cleanMeshDB_() {
  myMeshDB_->delete_mesh();
}


bool MeshComplex::loadFromFile(const QString &path) {
  qDebug() << "Readig " << path;
  return true;
}

bool MeshComplex::loadMeshFromFile(const QString &path) {
  auto rval = myMeshDB_->load_mesh(path.toStdString().c_str());
  if (moab::MB_SUCCESS != rval) {
    return false;
  }
  setupDual_();
  createGraphicsRepresentation_();
  return true;
}

void MeshComplex::removeGraphicsRepresentation_() {
   myScene_->clear();
   //delete myGraphics_;
   myGraphics_ = new QGraphicsItemGroup;
   myScene_->addItem(myGraphics_);
}


void MeshComplex::removeMesh() {
  removeGraphicsRepresentation_();
  cleanMeshDB_();
}

void MeshComplex::setupMeshDB_() {
  auto retval = myMeshDB_->tag_get_handle( "GraphicsNodes", 1, moab::MB_TYPE_OPAQUE, myGraphicsNodesTag_, moab::MB_TAG_CREAT|moab::MB_TAG_DENSE );
  checkDB_(retval);
}

void MeshComplex::setupDual_() {
  if (nullptr != myDual_) {
    delete myDual_;
  }
  myDual_ = new moab::DualTool(myMeshDB_);

}

void MeshComplex::updateSceneBox_() {
  double coords[6];
  myBBox_.get(coords);
  myScene_->setSceneRect(coords[0], coords[1], coords[3]-coords[0], coords[4]-coords[1]);
  //myScene_->update(coords[0], coords[1], coords[3]-coords[0], coords[4]-coords[1]);
  qDebug() << myScene_->sceneRect();
}

void MeshComplex::createGraphicsRepresentation_() {
  moab::Range vertices;
  myMeshDB_->get_entities_by_dimension(0,0,vertices);
  myBBox_.update(*myMeshDB_, vertices);
  for (auto &&handle : vertices) {
     addGraphicsNode_(handle);
  }
  moab::Range duals;
  std::vector<moab::EntityHandle> cells;
  myMeshDB_->get_entities_by_dimension(0, 2, cells);
  //myDual_->construct_dual(&(cells[0]), cells.size());
  qDebug() << "Number of seeds : " << cells.size();
  auto retval = myDual_->construct_dual(nullptr, 0);
  checkDB_(retval);
  retval = myDual_->get_dual_entities(2, &(cells[0]), cells.size(), duals);
  checkDB_(retval);

  //myMeshDB_->get_entities_by_dimension(0,2,cells);
  qDebug() << "Number of duals " << duals.size() ;
  for (auto &&handle : duals) {
     //addGraphicsCell_(handle);
     addDualCell_(handle);
  }
  updateSceneBox_();
}

/*
void MeshComplex::constructDualCells_(std::vector<moab::EntityHandle> &cells) {
  std::vector<moab::EntityHandle> cells;
  myMeshDB_->get_entities_by_dimension(0, 2, cells);
  myDual_->construct_dual(&(cells[0]), cells.size());
}
*/
