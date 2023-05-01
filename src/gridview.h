#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QGraphicsView>
#include <QWidget>

class GridView : public QGraphicsView
{
    Q_OBJECT
  protected:
    void mousePressEvent(QMouseEvent *event);

  public:
    GridView(QWidget *parent = nullptr);
};

#endif // GRIDVIEW_H
