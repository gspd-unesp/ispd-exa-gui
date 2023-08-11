#include "icon/schemaicon.h"
#include "icon/icon.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include "utils/iconSize.h"
#include "window/schemawindow.h"
#include "components/schema.h"
#include <QGraphicsItem>

SchemaIcon::SchemaIcon(Schema *owner, QGraphicsItem *parent)
    : Icon{owner, parent}
{
    this->owner      = owner;
    iconPath         = ":icons/cluster.png";
    iconPathSelected = ":icons/clusterSelected.png";
    
    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);
    
    this->setPixmap(pixmap);
}

SchemaIcon::SchemaIcon(SchemaIcon &icon) : Icon(icon) {
    this->owner = icon.owner;
}

void SchemaIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    this->owner->showConfiguration();
}

