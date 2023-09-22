#include "components/schemabuilder.h"
#include "components/conf/schemaconfiguration.h"
#include "components/schema.h"

SchemaBuilder *SchemaBuilder::setSchema(Schema *builderSchema)
{
    this->schema = builderSchema;
    return this;
}

SchemaBuilder *SchemaBuilder::setConf(SchemaConfiguration *builderConfiguration)
{
    this->conf = builderConfiguration;
    return this;
}

std::unique_ptr<Schema> SchemaBuilder::build()
{
    return std::make_unique<Schema>(this->schema, this->conf);
}
