#include "item/clustericon.h"
#include "utils/iconSize.h"
#include "window/cluster.h"
#include <QGraphicsItem>

ClusterIcon::ClusterIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    iconPath         = ":icons/cluster.png";
    iconPathSelected = ":icons/clusterSelected.png";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}

void ClusterIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    new ClusterWindow();
    Icon::mouseDoubleClickEvent(event);
}
