#include "components/switchbuilder.h"
#include "components/conf/machineconfiguration.h"
#include "components/machine.h"
#include "components/schema.h"
#include "components/switch.h"

SwitchBuilder *SwitchBuilder::setSchema(Schema *builderSchema)
{
    this->schema = builderSchema;
    return this;
}

SwitchBuilder *SwitchBuilder::setConf(SwitchConfiguration *builderConfiguration)
{
    this->conf = builderConfiguration;
    return this;
}

std::unique_ptr<Switch> SwitchBuilder::build()
{
    return std::make_unique<Switch>(this->schema, this->conf);
}
