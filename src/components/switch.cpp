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

Switch::Switch(Schema *schema, SwitchConfiguration const &conf)
    : conf(std::make_unique<SwitchConfiguration>(conf)), schema(schema)
{
    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setOwner(this)
            ->setPixmapPair(PixmapPair(switchPath, switchPathSelected))
            ->build());
}

Switch::~Switch()
{
    for (auto const &link : this->connectedLinks) {
        qDebug() << link.use_count();
        auto otherConnectable =
            link.get()->connections.getOtherConnectable(this);

        otherConnectable->removeConnectedLink(link.get());
        this->schema->links.erase(link.get()->getId());
    }

    this->connectedLinks.clear();
}

std::vector<std::shared_ptr<Link>> *Switch::getConnectedLinks()
{
    return &this->connectedLinks;
}

PixmapIcon *Switch::getIcon()
{
    return this->icon.get();
}

void Switch::setConnectedLinks(std::vector<std::shared_ptr<Link>> *map)
{
    this->connectedLinks = *map;
}

void Switch::removeConnectedLink(Link *link)
{
    std::erase_if(this->connectedLinks,
                  [link](auto iter) { return iter.get() == link; });
}

void Switch::addConnectedLink(std::shared_ptr<Link> link)
{
    this->connectedLinks.push_back(link);
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
    auto buffer  = std::string("[" + std::to_string(this->getId()) + "] = \"" +
                              this->conf->getName() + "\"");
    auto buffers = new std::vector<std::string>();
    buffers->push_back(buffer);
    for (auto &link : this->connectedLinks) {
        buffers->push_back("|- [" + std::to_string(link->getId()) + "] = " +
                           std::to_string(link->connections.begin->getId()) +
                           " -> \"" + link->conf->getName() + "\" -> " +
                           std::to_string(link->connections.end->getId()));
    }

    return std::unique_ptr<std::vector<std::string>>(buffers);
}

unsigned Switch::getId() const
{
    return this->id;
}
void Switch::setId(unsigned newId)
{
    this->id = newId;
}
