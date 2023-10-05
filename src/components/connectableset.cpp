#include "components/connectableset.h"
#include "components/cloner/connectablecloner.h"
#include "components/link.h"
#include "icon/pixmapicon.h"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Link>> *ConnectableSet::getConnectedLinks()
{
    return &this->connectedLinks;
}
void ConnectableSet::setConnectedLinks(std::vector<std::shared_ptr<Link>> *linksVector)
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
