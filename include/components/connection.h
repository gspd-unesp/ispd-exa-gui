#pragma once
#include "components/item.h"
#include "icon/pixmapicon.h"

#include <map>
#include <memory>

class Link;

class Connectable : public Item
{
public:
    virtual ~Connectable() = default;
    virtual std::map<unsigned, Link *> *getConnectedLinks()        = 0;
    virtual void setConnectedLinks(std::map<unsigned, Link *> *map) = 0;
    virtual void removeConnectedLink(Link *link) = 0;
    virtual void addConnectedLink(Link *link) = 0;
    virtual PixmapIcon *getIcon() = 0;
};
