#ifndef MESHCOMPLEX_H
#define MESHCOMPLEX_H

#include <moab/Interface.hpp>
#include <moab/BoundBox.hpp>
#include <moab/DualTool.hpp>

#include <QObject>

class QGraphicsItemGroup;
class QGraphicsScene;
class QPointF;

class MeshComplex : public QObject
{
  Q_OBJECT
public:
  explicit MeshComplex(QObject *parent = nullptr);
  void addNode(double x, double y);
  QGraphicsScene *getScene() const {return myScene_;}

signals:
  void message(const QString &message);

public slots:
  void addNode(const QPointF &p);
  bool loadFromFile(const QString &path);
  bool loadMeshFromFile(const QString &path);
  void removeMesh();

private:
    // Graphisc scene on which graphics representation of mesh elements live.
    QGraphicsScene *myScene_ = nullptr;

    // Group that collect all QGraphicsItems that represent cell complex
    QGraphicsItemGroup *myGraphics_ = nullptr;
    moab::Interface *myMeshDB_ = nullptr;
    moab::DualTool *myDual_ = nullptr;
    moab::BoundBox myBBox_;

    //! Tag for data set assiciating pointers to graphics nodes with vertices of mesh data base.
    moab::Tag myGraphicsNodesTag_;

    void addGraphicsNode_(moab::EntityHandle handle);
    void addGraphicsCell_(moab::EntityHandle handle);
    void addDualCell_(moab::EntityHandle handle);


    //! Check status code of MOAB operation
    void checkDB_(moab::ErrorCode retval);

    void cleanMeshDB_();

    void setupMeshDB_();
    void setupDual_();

    //! Create graphics items from entities in current mesh data base.
    void createGraphicsRepresentation_();

    //! Remove graphics entities but leave mesh data base intact.
    void removeGraphicsRepresentation_();
    void updateSceneBox_();
};

#endif // MESHCOMPLEX_H
