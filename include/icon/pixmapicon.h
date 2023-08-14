#pragma once
#include "icon.h"
#include "icon/pixmappair.h"
#include "qtimer.h"
#include <QGraphicsPixmapItem>
#include <QLabel>

#define CLICK_DURATION 200

class Connection;

class PixmapIcon : public QGraphicsPixmapItem, public Icon<Connection>
{
public:
    PixmapIcon(Connection *owner, PixmapPair pixmapPair);

    Connection *getOwner() override;
    void        toggleChoosen() override;
    void        updatePosition();
    bool        isChosen() override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QTimer      clickTimer = QTimer();
    Connection *owner      = nullptr;
    bool        chose      = false;
    PixmapPair  pixmapPair;
};
