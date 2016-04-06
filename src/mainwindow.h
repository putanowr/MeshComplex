#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MeshScene;
class QActionGroup;
class MeshComplex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setMeshComplex(MeshComplex *mc);

public slots:
    void showMessage(const QString &message);
    void openFile();
    void newMesh();
    void updateView();

private:
    void createActions();
    void setupConnections();
    void connectViewToComplex();
    void warn_(const QString &msg) const;

    Ui::MainWindow *ui;

    QAction *addPointAct;
    QAction *addEdgeAct;
    QAction *addCellAct;

    QActionGroup *myAddGroup;

    MeshComplex *myComplex = nullptr;

    QString myLastDir = "";
};

#endif // MAINWINDOW_H
