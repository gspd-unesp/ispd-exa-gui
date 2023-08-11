#pragma once

#include "components/cloner/cloner.h"
#include "components/machine.h"
#include <memory>

class SchemaCloner;

class MachineCloner : public Cloner
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent);
    std::unique_ptr<Item> clone() override;

private:
    Machine      *base;
    SchemaCloner *parent;
};
