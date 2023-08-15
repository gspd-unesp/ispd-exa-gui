#include "components/conf/schemaconfiguration.h"

SchemaConfiguration::SchemaConfiguration(std::string name, unsigned id)
    : name(name), id(id)
{}

unsigned SchemaConfiguration::getId()
{ 
    return this->id;
}
std::string SchemaConfiguration::getName()
{
    return this->name;
}

void SchemaConfiguration::setId(unsigned id)
{
    this->id = id;
}
void SchemaConfiguration::setName(std::string name)
{
    this->name = name;
}
