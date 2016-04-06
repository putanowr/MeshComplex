#include "meshview.h"
#include <QPointF>
#include <QRectF>
#include <QLineF>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "cmapplication.h"

MeshView::MeshView(QWidget *parent) : QGraphicsView(parent), myStep(0)
{
}

void MeshView::mousePressEvent(QMouseEvent *event)
{
  switch(myMode) {
    case Mode::ADD_NODE :
      addNode(event);
      break;
    case Mode::ADD_EDGE :
      myStep++;
      addEdge(event);
      break;
    case Mode::NO_ACTION :
      break;
    default :
      CMApplication::Warn("Unknown MeshView action");
  }
}

void MeshView::addEdge(QMouseEvent *event) {
  if (QGraphicsItem *item = itemAt(event->pos())) {
    QGraphicsEllipseItem *e = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
    if (e) {
        e->setBrush(Qt::red);
    }
    mySelectedItems.append(item);
    if (myStep == 2) {
      myStep = 0;
      addCell(mySelectedItems);
      mySelectedItems.clear();
    }
  }
}

void MeshView::addCell(ItemList &items)
{
   switch(items.count()) {
     case 2: {
       auto p1 = items.at(0)->scenePos();
       auto p2 = items.at(1)->scenePos();
       QLineF line(p1, p2);
       emit message(QString("Add line (%1,%2)--(%3,%4)").arg(p1.x()).arg(p1.y()).arg(p2.x()).arg(p2.y()));
       this->scene()->addLine(line);
    }
   }
}

void MeshView::addNode(QMouseEvent *event) {
  emit addNode(this->mapToScene(event->pos()));
}
