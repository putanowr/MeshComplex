#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MeshScene;
class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showMessage(const QString &message);

private:
    void createActions();
    void setupConnections();

    Ui::MainWindow *ui;
    MeshScene *myScene;

    QAction *addPointAct;
    QAction *addEdgeAct;
    QAction *addCellAct;

    QActionGroup *myAddGroup;
};

#endif // MAINWINDOW_H
