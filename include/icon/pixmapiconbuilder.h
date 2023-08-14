#pragma once
#include "icon/pixmappair.h"

class PixmapIcon;
class Connection;

class PixmapIconBuilder
{
public:
    PixmapIconBuilder();

    PixmapIconBuilder *setOwner(Connection *item);
    PixmapIconBuilder *setPixmapPair(PixmapPair pixmapPair);

    PixmapIcon *build();

private:
    Connection *owner;
    PixmapPair *pixmapPair;
};
