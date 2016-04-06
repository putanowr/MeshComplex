#include <QTransform>

#include <QActionGroup>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meshscene.h"
#include "meshview.h"

#include "cmapplication.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    setupConnections();

    QTransform m(1, 0, 0, -1, 0, 0);
    ui->graphicsView->setTransform(m);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}


void MainWindow::setMeshComplex(MeshComplex *mc)
{
   if(nullptr != mc)
   {
     myComplex = mc;
     ui->graphicsView->setScene(myComplex->getScene());
     ui->graphicsView->centerOn(0,0);
     connectViewToComplex();
   }
   else
   {
      ((CMApplication *)qApp)->Warn("Null mesh complex passed");
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showMessage(const QString &message)
{
   ui->feedbackText->append(message);
}

void MainWindow::setupConnections() {
  MeshView *mv = ui->graphicsView;
  connect(addPointAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddNode(bool)));
  connect(addEdgeAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddEdge(bool)));
  connect(addCellAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddCell(bool)));
  connect(mv, SIGNAL(message(const QString&)), this, SLOT(showMessage(const QString&)));

  connect(qApp, SIGNAL(message(const QString&)), this, SLOT(showMessage(const QString&)));

  // Connections from MainWindow menu
  connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(ui->actionNew_Mesh, SIGNAL(triggered()), this, SLOT(newMesh()));
}

void MainWindow::connectViewToComplex() {
  MeshView *mv = ui->graphicsView;
  connect(mv, SIGNAL(addNode(QPointF)), myComplex, SLOT(addNode(QPointF)));
}

void MainWindow::createActions() {
    addPointAct = new QAction("Add Point", this);
    addEdgeAct = new QAction("Adde Edge", this);
    addCellAct = new QAction("Add Cell", this);

    myAddGroup = new QActionGroup(this);
    myAddGroup->addAction(addPointAct);
    myAddGroup->addAction(addEdgeAct);
    myAddGroup->addAction(addCellAct);

    ui->mainToolBar->addActions(myAddGroup->actions());
}

void MainWindow::newMesh() {
  myComplex->removeMesh();
}

void MainWindow::openFile() {
  QFileDialog dialog(this, tr("Open mesh file"), myLastDir, tr("Mesh Files (*.vtk *.mesh)"));
  dialog.setFileMode(QFileDialog::ExistingFile);
  if (dialog.exec()) {
    myLastDir = dialog.directory().absolutePath();
    auto files = dialog.selectedFiles();
    if (!myComplex->loadMeshFromFile(files.at(0))) {
      warn_(QString("Failed reading file : %1").arg(files.at(0)));
    }
    updateView();
  }
}

void MainWindow::warn_(const QString &msg) const {
  QMessageBox msgBox;
  msgBox.setText(msg);
  msgBox.exec();
}

void MainWindow::updateView() {
  ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
}
