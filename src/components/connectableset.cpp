#include "components/connectableset.h"
#include "components/cloner/connectablecloner.h"
#include "components/conf/connectablesetconfiguration.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include "icon/seticonfactory.h"
#include <memory>
#include <vector>

ConnectableSet::ConnectableSet(Schema                      *schema,
                               ConnectableSetConfiguration *conf)
    : schema(schema), conf(std::make_unique<ConnectableSetConfiguration>(*conf))
{
    this->icon =
        std::unique_ptr<PixmapIcon>(SetIconFactory().iconBuilder(this));
}

std::vector<std::shared_ptr<Link>> *ConnectableSet::getConnectedLinks()
{
    return &this->connectedLinks;
}
void ConnectableSet::setConnectedLinks(
    std::vector<std::shared_ptr<Link>> *linksVector)
{
    this->connectedLinks = *linksVector;
}
void ConnectableSet::removeConnectedLink(Link *link)
{
    std::erase_if(this->connectedLinks,
                  [link](auto iter) { return iter.get() == link; });
}

void ConnectableSet::addConnectedLink(std::shared_ptr<Link> link)
{
    this->connectedLinks.push_back(link);
}

PixmapIcon *ConnectableSet::getIcon()
{
    return this->icon.get();
}

unsigned ConnectableSet::getId() const
{
    return this->id;
}

void ConnectableSet::setId(unsigned newId)
{
    this->id = newId;
}

std::unique_ptr<std::vector<std::string>> ConnectableSet::print()
{
    return std::make_unique<std::vector<std::string>>();
}

std::unique_ptr<ConnectableCloner> ConnectableSet::cloner(SchemaCloner *parent)
{
    return nullptr;
}

void ConnectableSet::showConfiguration()
{
    // TODO: implement showConfiguration
}

ItemConfiguration *ConnectableSet::getConf()
{
    return this->conf.get();
}
