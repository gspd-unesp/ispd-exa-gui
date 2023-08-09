#include "icon/machineicon.h"
#include "components/link.h"
#include "components/machine.h"
#include "icon/linkicon.h"
#include "utils/iconSize.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

MachineIcon::MachineIcon(unsigned id, const char *name, Machine *owner, QGraphicsItem *parent)
    : Icon{name, owner, parent}
{
    this->owner            = owner;
    this->id               = id;
    this->iconPath         = ":icons/pc.png";
    this->iconPathSelected = ":icons/pcSelected.png";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}

void MachineIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    this->owner->showConfiguration();
    
    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}
