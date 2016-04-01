#ifndef MESHSCENE_H
#define MESHSCENE_H

#include <QObject>
#include <QGraphicsScene>

class MeshScene : public QGraphicsScene
{
  Q_OBJECT

public:
    explicit MeshScene(QObject *parent = 0);

signals:

public slots:
};

#endif // MESHSCENE_H
