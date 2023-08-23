#include "components/schemabuilder.h"
#include "components/conf/schemaconfiguration.h"
#include "components/schema.h"

SchemaBuilder::SchemaBuilder()
{}

SchemaBuilder *SchemaBuilder::setSchema(Schema *schema)
{
    this->schema = schema;
    return this;
}

SchemaBuilder *SchemaBuilder::setConf(SchemaConfiguration *conf)
{
    this->conf = conf;
    return this;
}

Schema *SchemaBuilder::build()
{
    return new Schema(this->schema, this->conf);
}
