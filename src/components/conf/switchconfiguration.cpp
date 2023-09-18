#include "components/conf/switchconfiguration.h"

SwitchConfiguration::SwitchConfiguration(std::string_view const &name)
    : name(name)
{}

std::string SwitchConfiguration::getName() const
{
    return this->name;
}

void SwitchConfiguration::setName(std::string_view const &newName)
{
    this->name = newName;
}

