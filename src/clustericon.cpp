#include "src/clustericon.h"
#include "qgraphicsitem.h"

ClusterIcon::ClusterIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{

    auto pixmap = QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(70, 70));

    this->setPixmap(pixmap);
}
