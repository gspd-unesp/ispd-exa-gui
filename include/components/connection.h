#pragma once
#include "components/item.h"
#include <map>
#include <memory>

class Link;
class Icon;

class Connection : public Item
{
public:
    virtual std::map<unsigned, Link *> *getConnectedLinks()        = 0;
    virtual Icon *getIcon() = 0;
    virtual void setConnectedLinks(std::map<unsigned, Link *> *map) = 0;
    virtual void removeConnectedLink(Link *link) = 0;
    virtual void addConnectedLink(Link *link) = 0;
};
