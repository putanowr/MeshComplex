#include "graphicscell.h"
#include <QColor>
#include <QBrush>

QPen GraphicsCell::pen_= QPen(QBrush(Qt::black), 0.0);

GraphicsCell::GraphicsCell(const QVector<QPointF> &points) {
  setPolygon(QPolygonF{points});
  setup_();
}

void GraphicsCell::setup_() {
  setPen(pen_);
  setBrush(QBrush(Qt::yellow));
  setScale(0.8);
}
