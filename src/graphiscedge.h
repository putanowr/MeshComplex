#ifndef GRAPHISCEDGE_H
#define GRAPHISCEDGE_H

#include <QGraphicsLineItem>
#include <QObject>

class GraphiscEdge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit GraphiscEdge(QObject *parent = 0);

signals:

public slots:

};

#endif // GRAPHISCEDGE_H
