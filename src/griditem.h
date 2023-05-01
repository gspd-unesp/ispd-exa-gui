#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QWidget>
#include <QObject>

class GridItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    GridItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

  signals:
    void itemClicked();

  protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GRIDITEM_H
