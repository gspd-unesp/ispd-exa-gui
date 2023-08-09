#include "icon/switchicon.h"
#include "components/link.h"
#include "icon/linkicon.h"
#include "utils/iconSize.h"
#include "components/switch.h"

SwitchIcon::SwitchIcon(const char *name, Switch *owner, QGraphicsItem *parent)
    : Icon{name, owner, parent}
{
    this->owner            = owner;
    this->iconPath         = ":icons/switch.svg";
    this->iconPathSelected = ":icons/switch.svg";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}
