#include "griditem.h"

GridItem::GridItem(const QPixmap &pixmap, QGraphicsItem *parent) : QGraphicsPixmapItem{pixmap, parent}
{

}
void GridItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    qDebug() << "(" << this->pos().x() << " , " << this->pos().y() << ")" << "\n";
    QGraphicsItem::mousePressEvent(event);
}

void GridItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    auto pos = this->pos();
    auto height = this->scene()->sceneRect().height();
    auto width = this->scene()->sceneRect().width();

    if (pos.x() <= 0) {
        this->moveBy(- pos.x(), 0);
    }

    if (pos.y() <= 0) {
        this->moveBy(0, - pos.y());
    }

    if (pos.x() > width) {
        this->moveBy(- (pos.x() - width), 0);
    }

    if (pos.y() > height) {
        this->moveBy(0, - (pos.y() - height));
    }
}
