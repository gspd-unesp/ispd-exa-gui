#include "components/connectableset.h"
#include "components/cloner/connectablecloner.h"
#include "components/link.h"
#include "icon/pixmapicon.h"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Link>> *ConnectableSet::getConnectedLinks()
{
    return this->connectedLinks;
}
void ConnectableSet::setConnectedLinks(std::vector<std::shared_ptr<Link>> *linksVector)
{
    this->connectedLinks = linksVector;
}
void ConnectableSet::removeConnectedLink(Link *link)
{
    
}

void ConnectableSet::addConnectedLink(std::shared_ptr<Link> link)
{}
PixmapIcon *ConnectableSet::getIcon()
{}
unsigned ConnectableSet::getId() const
{}
void ConnectableSet::setId(unsigned newId)
{}
std::unique_ptr<std::vector<std::string>> ConnectableSet::print()
{}
std::unique_ptr<ConnectableCloner> ConnectableSet::cloner(SchemaCloner *parent)
{}
