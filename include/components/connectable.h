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
    virtual ~Connectable()                                          = default;
    virtual std::vector<std::shared_ptr<Link>> *getConnectedLinks() = 0;
    virtual void                                setConnectedLinks(
                                       std::vector<std::shared_ptr<Link>> *linksVector) = 0;
    virtual void        removeConnectedLink(Link *link)                     = 0;
    virtual void        addConnectedLink(std::shared_ptr<Link> link)        = 0;
    virtual PixmapIcon *getIcon()                                           = 0;
    virtual unsigned    getId() const                                       = 0;
    virtual void        setId(unsigned newId)                               = 0;
    virtual std::unique_ptr<std::vector<std::string>> print()               = 0;
    virtual std::unique_ptr<ConnectableCloner> cloner(SchemaCloner *parent) = 0;
};
