#ifndef MESHVIEW_H
#define MESHVIEW_H

#include <QGraphicsView>

class QPointF;

class MeshView : public QGraphicsView
{
  Q_OBJECT

  enum class Mode
  {
    NO_ACTION,
    ADD_NODE,
    ADD_EDGE,
    ADD_CELL
  };
public:
 using ItemList = QList<QGraphicsItem*>;

public:
    explicit MeshView(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void message(const QString &msg);
    void addNode(const QPointF &pos);

public slots:
    void setMode(Mode mode) { myMode = mode; myStep = 0;}
    void setModeToAddNode(bool) {setMode(Mode::ADD_NODE);}
    void setModeToAddEdge(bool) {setMode(Mode::ADD_EDGE);}
    void setModeToAddCell(bool) {setMode(Mode::ADD_CELL);}

private:
    void addNode(QMouseEvent *event);
    void addEdge(QMouseEvent *event);
    void addCell(ItemList &items);

private:
    Mode myMode;
    unsigned int myStep = 0;
    ItemList mySelectedItems;
};

#endif // MESHVIEW_H
