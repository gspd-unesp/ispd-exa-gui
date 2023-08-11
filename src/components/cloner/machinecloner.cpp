
#include "components/cloner/machinecloner.h"
#include "components/cloner/schemacloner.h"
#include "components/machine.h"
#include <memory>

MachineCloner::MachineCloner(Machine *base, SchemaCloner *parent)
{}

std::unique_ptr<Machine> MachineCloner::clone()
{
    std::unique_ptr<Machine> clonedMachine = std::make_unique<Machine>(nullptr, 0, "");

    return clonedMachine;
}
