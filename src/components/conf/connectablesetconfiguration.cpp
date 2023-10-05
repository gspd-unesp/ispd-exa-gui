#include "components/conf/connectablesetconfiguration.h"
ConnectableSetConfiguration::ConnectableSetConfiguration(
    std::string_view const &name) : name(name)
{}

std::string ConnectableSetConfiguration::getName() const
{
    return this->name;
}
void ConnectableSetConfiguration::setName(std::string_view const &name)
{
    this->name = name;
}
