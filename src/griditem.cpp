#include "griditem.h"

/*
 * Create the item following the QGraphicsPixmapItem constructor
 */
GridItem::GridItem(const QPixmap &pixmap, QGraphicsItem *parent) : QGraphicsPixmapItem{pixmap, parent}
{
}

/*
 * Configure the event of clicking the item to print the position of it.
 * Useful for DEBUG.
 */
void GridItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << "(" << this->pos().x() << " , " << this->pos().y() << ")"
             << "\n";
    QGraphicsItem::mousePressEvent(event);
}

/*
 * Configure the event of releasing the mouse to check if the item is
 * inside its scene, if it's not, move it inside.
 */
void GridItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    auto pos = this->pos();
    auto height = this->scene()->sceneRect().height();
    auto width = this->scene()->sceneRect().width();

    if (pos.x() <= 0)
    {
        this->moveBy(-pos.x(), 0);
    }

    if (pos.y() <= 0)
    {
        this->moveBy(0, -pos.y());
    }

    if (pos.x() > width)
    {
        this->moveBy(-(pos.x() - width), 0);
    }

    if (pos.y() > height)
    {
        this->moveBy(0, -(pos.y() - height));
    }
}
