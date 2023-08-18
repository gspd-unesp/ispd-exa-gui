#include "icon/pixmapiconbuilder.h"
#include "icon/pixmapicon.h"
#include "components/connection.h"
#include "icon/pixmappair.h"

PixmapIconBuilder::PixmapIconBuilder()
{}

PixmapIconBuilder *PixmapIconBuilder::setOwner(Connectable *owner)
{
    this->owner = owner;
    return this;
}

PixmapIconBuilder *PixmapIconBuilder::setPixmapPair(PixmapPair pixmapPair)
{
    this->pixmapPair = &pixmapPair;
    return this;
}

PixmapIcon *PixmapIconBuilder::build()
{
    return new PixmapIcon(this->owner, PixmapPair(*this->pixmapPair));
}
