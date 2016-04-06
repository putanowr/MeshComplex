#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include <QGraphicsEllipseItem>
#include <QRectF>

class GraphicsNode : public QGraphicsEllipseItem
{
public:
    GraphicsNode(double x, double y);
    static void setRadius(double r);
    static void setScale(double s);
signals:

public slots:

public:
  static QRectF nodeRect;
  static double scale;

  void setup_(double x=0.0, double y=0.0);
};

#endif // GRAPHICSNODE_H
