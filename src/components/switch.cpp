#include "components/switch.h"
#include "components/link.h"
#include <memory>

Switch::Switch(Schema *schema, unsigned id, const char *name)
{
    this->schema = schema;
    this->id = id;
    this->name = name;

    this->connectedLinks = std::map<unsigned, Link *>();
    this->icon = std::make_unique<SwitchIcon>(name, this);
}

std::map<unsigned, Link *> *Switch::getConnectedLinks()
{
    return &this->connectedLinks;
}

SwitchIcon *Switch::getIcon()
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
