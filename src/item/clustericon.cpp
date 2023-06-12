#include "item/clustericon.h"
#include "drawingtable/scene.h"
#include <QGraphicsItem>

ClusterIcon::ClusterIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    isSelected = false;
    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(50, 50));

    this->setPixmap(pixmap);
}

void ClusterIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Icon::mousePressEvent(event);
    select(); // Chama a função select() da classe base Icon
}

void ClusterIcon::select()
{
    if (!isSelected) {
        isSelected = true;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPathSelected)).scaled(QSize(55, 55));
        this->setPixmap(pixmap);
    } else {
        isSelected = false;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(50, 50));
        this->setPixmap(pixmap);
    }
}
