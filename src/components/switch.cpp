#include "components/switch.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/pixmappair.h"
#include "utils/iconPath.h"
#include <memory>

Switch::Switch(Schema *schema, unsigned id, const char *name)
{
    this->schema = schema;
    this->id     = id;
    this->name   = name;

    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setOwner(this)
            ->setPixmapPair(PixmapPair(switchPath, switchPathSelected))
            ->build());
}

Switch::~Switch()
{
    for (auto [linkId, link] : this->connectedLinks) {
        Connection *otherIcon = (link->connections.begin == this)
                                    ? link->connections.end
                                    : link->connections.begin;

        otherIcon->removeConnectedLink(link);

        this->schema->deleteLink(linkId);
    }
}

std::map<unsigned, Link *> *Switch::getConnectedLinks()
{
    return &this->connectedLinks;
}

PixmapIcon *Switch::getIcon()
{
    return this->icon.get();
}

void Switch::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connectedLinks = *map;
}

void Switch::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connectedLinks.find(link->id);

    if (linkToRemove != connectedLinks.end()) {
        this->connectedLinks.erase(linkToRemove);
    }
}

void Switch::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connectedLinks.find(link->id);

    if (linkToAdd == connectedLinks.end()) {
        this->connectedLinks.insert(std::pair(link->id, link));
    }
}

std::string Switch::getName()
{
    return this->name;
}

void Switch::showConfiguration()
{}
