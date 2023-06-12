#include "item/machineicon.h"
#include "drawingtable/scene.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

MachineIcon::MachineIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    isSelected = false;
    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(50, 50));

    this->setPixmap(pixmap);
}

void MachineIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Icon::mousePressEvent(event);
    select();
}

void MachineIcon::select()
{
    if (!isSelected) {
        this->isSelected = true;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPathSelected)).scaled(QSize(55, 55));
        this->setPixmap(pixmap);
    } else {
        this->isSelected = false;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(50, 50));
        this->setPixmap(pixmap);
    }
}

