#include "item/clustericon.h"
#include <QGraphicsItem>
#include "utils/iconSize.h"

ClusterIcon::ClusterIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    iconPath         = ":icons/cluster.png";
    iconPathSelected = ":icons/clusterSelected.png";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}
