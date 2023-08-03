#include "item/schemaicon.h"
#include "qdebug.h"
#include "utils/iconSize.h"
#include "window/schemawindow.h"
#include <QGraphicsItem>

SchemaIcon::SchemaIcon(const char *name, Schema *owner, QGraphicsItem *parent)
    : Icon{name, parent}
{
    this->owner      = owner;
    this->window     = new SchemaWindow(this->owner);
    iconPath         = ":icons/cluster.png";
    iconPathSelected = ":icons/clusterSelected.png";

    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}

void SchemaIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO: reform this
    qDebug() << "É Aqui o problema?";
    this->window->show();
    Icon::mouseDoubleClickEvent(event);
}

