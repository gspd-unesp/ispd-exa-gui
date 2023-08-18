#pragma once
#include "icon.h"
#include "icon/pixmappair.h"
#include "qtimer.h"
#include <QGraphicsPixmapItem>
#include <QLabel>

#define CLICK_DURATION 200

class Connectable;

class PixmapIcon : public QGraphicsPixmapItem, public Icon
{
public:
    PixmapIcon(Connectable *owner, PixmapPair pixmapPair);

    Component *getOwner() override;
    void  toggleChoosen() override;
    void  updatePosition() override;
    bool  isChosen() override;
    void  toggleChosenIfInside(QRectF selectionAreaRect) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QTimer      clickTimer = QTimer();
    Connectable *owner      = nullptr;
    bool        chose      = false;
    PixmapPair  pixmapPair;
};
