#include "icon/pixmapicon.h"
#include "components/connection.h"
#include "components/link.h"
#include "icon/linkicon.h"
#include <QGraphicsItem>
#include <chrono>

PixmapIcon::PixmapIcon(Connection *owner, PixmapPair pixmapPair)
    : owner(owner), pixmapPair(pixmapPair)
{
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setPixmap(this->pixmapPair.getNormal());
    this->owner = owner;
}

Connection *PixmapIcon::getOwner()
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

void PixmapIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
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
        link->getIcon()->updatePositions();
    }
}

bool PixmapIcon::isChosen()
{
    return this->chose;
}
