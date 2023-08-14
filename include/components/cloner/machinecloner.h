#pragma once

#include "components/cloner/cloner.h"
#include "components/machine.h"
#include "qpoint.h"
#include <memory>

class MachineConfiguration;
class SchemaCloner;
class Schema;

class MachineCloner : public Cloner<Machine>
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent);
    std::unique_ptr<Machine> clone(Schema *schema) override;

private:
    MachineConfiguration *clonedConf;
    QPointF               pos;
    SchemaCloner         *parent;
};
