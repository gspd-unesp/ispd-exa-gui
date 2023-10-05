#include "components/connectablesetbuilder.h"
#include "components/connectableset.h"
#include "components/conf/connectablesetconfiguration.h"
#include <memory>

ConnectableSetBuilder *ConnectableSetBuilder::setSchema(Schema *baseSchema)
{
    this->schema = baseSchema;
    return this;
}

ConnectableSetBuilder *ConnectableSetBuilder::setConf(
    ConnectableSetConfiguration const &baseConf)
{
    this->conf = std::make_unique<ConnectableSetConfiguration>(baseConf);
    return this;
}

std::unique_ptr<ConnectableSet> ConnectableSetBuilder::build()
{
    auto newConnectable = std::make_unique<ConnectableSet>(this->schema, this->conf.get());
    return newConnectable;
}
