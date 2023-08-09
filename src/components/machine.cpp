#include "components/machine.h"
#include "components/conf/linkconf.h"
#include "components/item.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/machineicon.h"
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

    this->icon = std::make_unique<MachineIcon>(id, name);
    this->icon->setLinks(&this->connected_links);
    this->icon->setItem(this);
}

Machine::~Machine()
{
    qDebug() << "Deleting " << this->name.c_str();
}

void Machine::showConfiguration()
{
    machineIconConfiguration *machineIconConfig =
        new machineIconConfiguration(this->icon->getName()->c_str());
    machineIconConfig->show();
}

MachineIcon *Machine::getIcon()
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

void Machine::removeConnectedLink(Link *link) {
    auto linkToRemove = this->connected_links.find(link->id);

    if (linkToRemove != connected_links.end()) {
        this->connected_links.erase(linkToRemove);
    }
}
void Machine::addConnectedLink(Link *link) {
    auto linkToAdd = this->connected_links.find(link->id);

    if (linkToAdd == connected_links.end()) {
        this->connected_links.insert(std::pair(link->id, link));
    }
}
