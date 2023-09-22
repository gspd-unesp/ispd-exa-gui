#include "components/machinebuilder.h"
#include "components/conf/machineconfiguration.h"
#include "components/machine.h"
#include "components/schema.h"

MachineBuilder *MachineBuilder::setSchema(Schema *baseSchema)
{
    this->schema = baseSchema;
    return this;
}

MachineBuilder *MachineBuilder::setConf(MachineConfiguration const &baseConf)
{
    this->conf = std::make_unique<MachineConfiguration>(baseConf);
    return this;
}

std::unique_ptr<Machine> MachineBuilder::build()
{
    return std::make_unique<Machine>(this->schema, this->conf.get());
}
