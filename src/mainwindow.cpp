#include <QTransform>
#include <QActionGroup>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meshscene.h"
#include "meshview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myScene = new MeshScene(this);

    createActions();
    setupConnections();

    ui->graphicsView->setScene(myScene);
    QTransform m(1, 0, 0, -1, 0, 0);
    ui->graphicsView->setTransform(m);
    myScene->addLine(0,0,100,100);
    myScene->addLine(0,0,-100,100);
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
  connect(addPointAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddPoint(bool)));
  connect(addEdgeAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddEdge(bool)));
  connect(addCellAct, SIGNAL(triggered(bool)), mv, SLOT(setModeToAddCell(bool)));
  connect(mv, SIGNAL(message(const QString&)), this, SLOT(showMessage(const QString&)));
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
