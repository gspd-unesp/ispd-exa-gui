#include "components/switch.h"
#include "components/cloner/switchcloner.h"
#include "components/conf/switchconfiguration.h"
#include "components/connectable.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/pixmappair.h"
#include "utils/iconPath.h"
#include <memory>

Switch::Switch(Schema *schema, SwitchConfiguration *conf)
    : conf(conf), schema(schema)
{
    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setOwner(this)
            ->setPixmapPair(PixmapPair(switchPath, switchPathSelected))
            ->build());
}

Switch::~Switch()
{
    for (auto [linkId, link] : this->connectedLinks) {
        Connectable *otherIcon = (link->connections.begin == this)
                                     ? link->connections.end
                                     : link->connections.begin;

        this->schema->links.erase(linkId);
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
    auto linkToRemove = this->connectedLinks.find(link->conf->getId());

    if (linkToRemove != connectedLinks.end()) {
        this->connectedLinks.erase(linkToRemove);
    }
}

void Switch::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connectedLinks.find(link->conf->getId());

    if (linkToAdd == connectedLinks.end()) {
        this->connectedLinks.insert(std::pair(link->conf->getId(), link));
    }
}

std::string Switch::getName()
{
    return this->conf->getName();
}

void Switch::showConfiguration()
{}

SwitchConfiguration *Switch::getConf()
{
    return this->conf.get();
}

std::unique_ptr<ConnectableCloner> Switch::cloner(SchemaCloner *parent)
{
    return std::make_unique<SwitchCloner>(this, parent);
}

std::unique_ptr<std::vector<std::string>> Switch::print()
{
    auto buffer  = std::string("[" + std::to_string(this->conf->getId()) +
                              "] = \"" + this->conf->getName() + "\"");
    auto buffers = new std::vector<std::string>();
    buffers->push_back(buffer);
    for (auto &[id, link] : this->connectedLinks) {
        buffers->push_back(
            "|- [" + std::to_string(link->conf->getId()) + "] = " +
            std::to_string(link->connections.begin->getConf()->getId()) +
            " -> \"" + link->conf->getName() + "\" -> " +
            std::to_string(link->connections.end->getConf()->getId()));
    }

    return std::unique_ptr<std::vector<std::string>>(buffers);
}
