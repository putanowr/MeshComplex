#ifndef GRAPHISCCELL_H
#define GRAPHISCCELL_H

#include <QGraphicsPolygonItem>
#include <QVector>
#include <QPointF>
#include <QPen>

class GraphicsCell : public QGraphicsPolygonItem
{
public:
  explicit GraphicsCell(const QVector<QPointF> &points);

signals:

public slots:

private:
  void setup_();

  static QPen pen_;
};

#endif // GRAPHISCCELL_H
