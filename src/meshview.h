#ifndef MESHVIEW_H
#define MESHVIEW_H

#include <QGraphicsView>

class MeshView : public QGraphicsView
{
  Q_OBJECT

  enum class Mode
  {
    NO_ACTION,
    ADD_POINT,
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
    void message(QString &msg);

public slots:
    void setMode(Mode mode) { myMode = mode; myStep = 0;}
    void setModeToAddPoint(bool) {setMode(Mode::ADD_POINT);}
    void setModeToAddEdge(bool)  {setMode(Mode::ADD_EDGE);}
    void setModeToAddCell(bool)  {setMode(Mode::ADD_CELL);}

private:
    void addPoint(QMouseEvent *event);
    void addEdge(QMouseEvent *event);
    void addCell(ItemList &items);

private:
    Mode myMode;
    unsigned int myStep = 0;
    ItemList mySelectedItems;
};

#endif // MESHVIEW_H
