#include "graphicsnode.h"
#include <QRectF>
#include <QBrush>

static double r=4.0;
QRectF GraphicsNode::nodeRect = QRectF{-r,-r,2*r,2*r};
double GraphicsNode::scale = 1.0;

GraphicsNode::GraphicsNode(double x, double y) : QGraphicsEllipseItem(GraphicsNode::nodeRect)
{
    setup_(x,y);
}

void GraphicsNode::setScale(double s) {
    scale = s;
}

void GraphicsNode::setRadius(double r) {
  nodeRect = QRectF{-r,-r,2*r,2*r};
}

void GraphicsNode::setup_(double x, double y) {
  setPos(x,y);
  setScale(scale);
  setBrush(QBrush(Qt::red));
  setFlag(QGraphicsItem::ItemIgnoresTransformations);
  setZValue(100.0);
}
