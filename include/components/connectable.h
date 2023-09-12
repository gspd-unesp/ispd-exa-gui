#pragma once
#include "components/component.h"
#include "icon/pixmapicon.h"

#include <map>
#include <memory>

class Link;
class ConnectableCloner;
class SchemaCloner;

class Connectable : public Component
{
public:
    virtual ~Connectable()                                  = default;
    virtual std::map<unsigned, Link *> *getConnectedLinks() = 0;
    virtual void        setConnectedLinks(std::map<unsigned, Link *> *map) = 0;
    virtual void        removeConnectedLink(Link *link)                    = 0;
    virtual void        addConnectedLink(Link *link)                       = 0;
    virtual PixmapIcon *getIcon()                                          = 0;
    virtual std::unique_ptr<std::vector<std::string>> print()              = 0;
    virtual std::unique_ptr<ConnectableCloner> cloner(SchemaCloner *parent) = 0;
};
