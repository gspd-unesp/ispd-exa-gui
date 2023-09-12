#include "components/machinebuilder.h"
#include "components/conf/machineconfiguration.h"
#include "components/machine.h"
#include "components/schema.h"

MachineBuilder::MachineBuilder()
{}

MachineBuilder *MachineBuilder::setSchema(Schema *schema)
{
    this->schema = schema;
    return this;
}

MachineBuilder *MachineBuilder::setConf(MachineConfiguration *conf)
{
    this->conf = conf;
    return this;
}

std::unique_ptr<Machine> MachineBuilder::build()
{
    return std::make_unique<Machine>(this->schema, this->conf);
}
