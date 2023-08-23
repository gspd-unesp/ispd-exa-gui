#include "components/conf/switchconfiguration.h"

SwitchConfiguration::SwitchConfiguration(std::string name, unsigned id)
    : id(id), name(name)
{}

unsigned SwitchConfiguration::getId()
{ 
    return this->id;
}
std::string SwitchConfiguration::getName()
{
    return this->name;
}

void SwitchConfiguration::setId(unsigned id)
{
    this->id = id;
}
void SwitchConfiguration::setName(std::string name)
{
    this->name = name;
}

