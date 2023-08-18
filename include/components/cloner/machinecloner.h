#pragma once

#include "components/cloner/connectablecloner.h"
#include "icon/pixmapicon.h"
#include "qpoint.h"
#include <memory>

class MachineConfiguration;
class SchemaCloner;
class Schema;
class Machine;

class MachineCloner : public ConnectableCloner
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent);
    Connectable *clone(Schema *schema) override;

private:
    MachineConfiguration *clonedConf;
    QPointF               pos;
    SchemaCloner         *parent;
};
