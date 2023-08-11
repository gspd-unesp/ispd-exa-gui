#include "icon/switchicon.h"
#include "components/link.h"
#include "components/switch.h"
#include "icon/linkicon.h"
#include "utils/iconSize.h"

SwitchIcon::SwitchIcon(Switch *owner, QGraphicsItem *parent)
    : Icon{owner, parent}
{
    this->owner            = owner;
    this->iconPath         = ":icons/switch.svg";
    this->iconPathSelected = ":icons/switch.svg";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}
