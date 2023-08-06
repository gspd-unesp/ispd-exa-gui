#include "components/machine.h"
#include "components/conf/linkconf.h"
#include "components/item.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/machineicon.h"
#include "window/machineconfiguration.h"
#include <map>
#include <vector>

Machine::Machine(Schema *schema, unsigned id, const char *name)
{
    this->schema          = schema;
    this->id              = id;
    this->connected_links = new std::map<unsigned, Link *>();

    this->icon = new MachineIcon(id, name);
    this->icon->setLinks(this->connected_links);
    this->icon->setItem(this);
}

Machine::~Machine()
{
    for (auto link = this->connected_links->begin();
         link != this->connected_links->end();
         link++) {
        Link *deletableLink = (*link).second;

        delete (deletableLink);

        this->schema->links->erase(link->first);
    }

    delete this->connected_links;
}

void Machine::showConfiguration()
{
    machineIconConfiguration *machineIconConfig =
        new machineIconConfiguration(this->icon->getName()->c_str());
    machineIconConfig->show();
}

Icon *Machine::getIcon()
{
    return this->icon;
}

std::map<unsigned, Link *> *Machine::get_connected_links()
{
    return this->connected_links;
}

void Machine::set_connectedLinks(std::map<unsigned, Link *> *map)
{
    this->connected_links = map;
}
