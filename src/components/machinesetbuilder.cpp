#include "components/machinesetbuilder.h"
#include "components/machineset.h"
#include "components/conf/machinesetconfiguration.h"
#include <memory>

ConnectableSetBuilder *ConnectableSetBuilder::setSchema(Schema *baseSchema)
{
    this->schema = baseSchema;
    return this;
}

ConnectableSetBuilder *ConnectableSetBuilder::setConf(
    MachineSetConfiguration const &baseConf)
{
    this->conf = std::make_unique<MachineSetConfiguration>(baseConf);
    return this;
}

std::unique_ptr<MachineSet> ConnectableSetBuilder::build()
{
    auto newConnectable = std::make_unique<MachineSet>(this->schema, this->conf.get());
    return newConnectable;
}
