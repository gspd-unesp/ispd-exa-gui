#include "icon/schemaicon.h"
#include "icon/icon.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include "utils/iconSize.h"
#include "window/schemawindow.h"
#include "components/schema.h"
#include <QGraphicsItem>

SchemaIcon::SchemaIcon(const char *name, Schema *owner, QGraphicsItem *parent)
    : Icon{name, owner, parent}
{
    this->owner      = owner;
    this->window     = new SchemaWindow(this->owner);
    iconPath         = ":icons/cluster.png";
    iconPathSelected = ":icons/clusterSelected.png";
    
    auto pixmap =
        QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);
    
    this->setPixmap(pixmap);
}
