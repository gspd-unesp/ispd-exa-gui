#pragma once
#include "components/item.h"
/* #include "icon/pixmapicon.h" */

#include <map>
#include <memory>

class PixmapIcon;
class Link;

class Connection : public Item<PixmapIcon>
{
public:
    virtual ~Connection() = default;
    virtual std::map<unsigned, Link *> *getConnectedLinks()        = 0;
    virtual void setConnectedLinks(std::map<unsigned, Link *> *map) = 0;
    virtual void removeConnectedLink(Link *link) = 0;
    virtual void addConnectedLink(Link *link) = 0;
    virtual PixmapIcon *getIcon() = 0;
};
