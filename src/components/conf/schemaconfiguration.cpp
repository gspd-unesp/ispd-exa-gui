#include "components/conf/schemaconfiguration.h"

SchemaConfiguration::SchemaConfiguration(std::string_view const &name)
    : name(name)
{}

std::string SchemaConfiguration::getName() const
{
    return this->name;
}

void SchemaConfiguration::setName(std::string_view const &newName)
{
    this->name = newName;
}
