
#include "components/cloner/machinecloner.h"
#include "components/cloner/schemacloner.h"
#include "components/machine.h"
#include <memory>

MachineCloner::MachineCloner(Machine *base, SchemaCloner *parent)
{
    this->base = base;
    this->parent = parent;
}

std::unique_ptr<Item> MachineCloner::clone()
{
    std::unique_ptr<Machine> clonedMachine = std::make_unique<Machine>(nullptr, 0, "");

    clonedMachine->connected_links = this->base->connected_links;
    clonedMachine->load = this->base->load;

    return clonedMachine;
}
