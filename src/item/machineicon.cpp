#include "item/machineicon.h"
#include "utils/iconSize.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

MachineIcon::MachineIcon(unsigned id, const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    this->id               = id;
    this->iconPath         = ":icons/pc.png";
    this->iconPathSelected = ":icons/pcSelected.png";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}
