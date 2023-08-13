#include "icon/pixmapiconbuilder.h"
#include "icon/pixmapicon.h"
#include "components/connection.h"

PixmapIconBuilder::PixmapIconBuilder()
{}

PixmapIconBuilder *PixmapIconBuilder::setOwner(Connection *owner)
{
    this->owner = owner;
    return this;
}

PixmapIconBuilder *PixmapIconBuilder::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    return this;
}

PixmapIcon *PixmapIconBuilder::build()
{
    return new PixmapIcon(owner, pixmap);
}
