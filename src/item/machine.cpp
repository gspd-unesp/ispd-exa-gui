#include "item/machine.h"
#include "item/item.h"
#include "item/link.h"
#include "item/machineicon.h"
#include "load/linkload.h"
#include "schema.h"
#include "window/machineconfiguration.h"
#include <map>
#include <vector>

Machine::Machine(Schema *schema, unsigned id, const char *name)
{
    this->schema = schema;
    this->id     = id;
    this->links  = new std::map<unsigned, Link *>();

    this->icon = new MachineIcon(id, name);
    this->icon->setLinks(this->links);
}

Machine::~Machine()
{
    for (auto link = this->links->begin(); link != this->links->end(); link++) {
        Link *deletableLink = (*link).second;

        delete (deletableLink);

        this->schema->links->erase(link->first);
    }

    delete this->links;
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
