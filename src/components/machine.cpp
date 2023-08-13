#include "components/machine.h"
#include "components/conf/linkconf.h"
#include "components/item.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include "icon/pixmapiconbuilder.h"
#include "utils/iconPath.h"
#include "utils/iconSize.h"
#include "window/machineconfiguration.h"
#include <map>
#include <memory>
#include <vector>

Machine::Machine(Schema *schema, unsigned id, const char *name)
{
    this->name            = std::string(name);
    this->schema          = schema;
    this->id              = id;
    this->connected_links = std::map<unsigned, Link *>();

    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setPixmap(QPixmap(machinePath).scaled(iconSize))
            ->setOwner(this)
            ->build());
}

Machine::~Machine()
{
    for (auto [linkId, link] : this->connected_links) {
        Connection *otherIcon = (link->connections.begin == this)
                                    ? link->connections.end
                                    : link->connections.begin;

        otherIcon->removeConnectedLink(link);

        this->schema->deleteLink(linkId);
    }

    qDebug() << "Deleting " << this->name.c_str();
}

void Machine::showConfiguration()
{
    machineIconConfiguration *machineIconConfig =
        new machineIconConfiguration(this->name.c_str());
    machineIconConfig->show();
}

PixmapIcon *Machine::getIcon()
{
    return this->icon.get();
}

std::map<unsigned, Link *> *Machine::getConnectedLinks()
{
    return &this->connected_links;
}

void Machine::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connected_links = *map;
}

void Machine::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connected_links.find(link->id);

    if (linkToRemove != connected_links.end()) {
        this->connected_links.erase(linkToRemove);
    }
}
void Machine::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connected_links.find(link->id);

    if (linkToAdd == connected_links.end()) {
        this->connected_links.insert(std::pair(link->id, link));
    }
}

Machine::Machine(Machine &machine)
{
    this->name            = "";
    this->schema          = nullptr;
    this->load            = machine.load;
    this->connected_links = machine.connected_links;
    // TODO USE MACHINEBUILDER
    /* this->icon            = std::make_unique<MachineIcon>(this); */
    /* this->icon->configurate(machine.getIcon()->getConf()); */
    this->id = 0;
}

std::unique_ptr<Machine> Machine::clone()
{
    return std::make_unique<Machine>(*this);
}
