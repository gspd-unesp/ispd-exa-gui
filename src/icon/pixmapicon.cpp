#include "icon/pixmapicon.h"
#include "components/connection.h"
#include "qgraphicsitem.h"

PixmapIcon::PixmapIcon(Connection *owner, QPixmap pixmap)
{
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setPixmap(pixmap);
    this->owner = owner;
}

Connection *PixmapIcon::getOwner()
{
    return owner;
}

void PixmapIcon::toggleSelect()
{
    if (this->isSelected()) {
        this->setSelected(false);
        return;
    }
    this->setSelected(true);
}

void PixmapIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    this->owner->showConfiguration();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}
