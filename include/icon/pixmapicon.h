#pragma once
#include "qlabel.h"
#include <QGraphicsPixmapItem>
#include "icon.h"

class Connection;

class PixmapIcon : public QGraphicsPixmapItem, public Icon<Connection>
{
public:
    PixmapIcon(Connection *owner, QPixmap pixmap);

    Connection *getOwner() override;

    void toggleSelect() override;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Connection *owner;
};
