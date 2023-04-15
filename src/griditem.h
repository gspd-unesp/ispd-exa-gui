#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QWidget>

class GridItem : public QGraphicsPixmapItem
{
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  public:
    explicit GridItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
};

#endif // GRIDITEM_H
