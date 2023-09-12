#include "icon/pixmapicon.h"
#include "components/connectable.h"
#include "components/connectable.h"
#include "components/link.h"
#include "icon/linkicon.h"
#include <QGraphicsItem>
#include <chrono>

PixmapIcon::PixmapIcon(Connectable *owner, PixmapPair pixmapPair)
    : owner(owner), pixmapPair(pixmapPair)
{
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setPixmap(this->pixmapPair.getNormal());
    this->owner = owner;
}

Component *PixmapIcon::getOwner()
{
    return owner;
}

void PixmapIcon::toggleChoosen()
{
    if (!this->chose) {
        this->setPixmap(this->pixmapPair.getSelected());
    }
    else {
        this->setPixmap(this->pixmapPair.getNormal());
    }

    this->chose = !this->chose;
}

void PixmapIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << this->owner->getConf()->getName().c_str() << this->owner->getConf()->getId();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void PixmapIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    this->clickTimer.start();
    this->owner->showConfiguration();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

void PixmapIcon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->clickTimer.setInterval(CLICK_DURATION);
    QGraphicsPixmapItem::mouseMoveEvent(event);
    this->updatePosition();
}

void PixmapIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->clickTimer.stop();
    if (this->clickTimer.interval() < CLICK_DURATION) {
        this->toggleChoosen();
    }
    this->clickTimer.setInterval(0);

    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void PixmapIcon::updatePosition()
{
    for (auto &[id, link] : *this->owner->getConnectedLinks()) {
        link->getIcon()->updatePosition();
    }
}

bool PixmapIcon::isChosen()
{
    return this->chose;
}

void PixmapIcon::toggleChosenIfInside(QRectF area)
{
    if (area.contains(this->sceneBoundingRect()) && !this->isChosen()) {
        this->toggleChoosen();
    }
}
