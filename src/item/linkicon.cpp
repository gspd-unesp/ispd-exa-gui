#include "item/linkicon.h"
#include "utils/iconSize.h"
#include "qgraphicsitem.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

LinkIcon::LinkIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    iconPath         = ":/icons/connection.png";
    auto pixmap = QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);

    this->setPixmap(pixmap);
}
