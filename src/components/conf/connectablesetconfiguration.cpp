#include "components/conf/connectablesetconfiguration.h"

std::string ConnectableSetConfiguration::getName() const
{
    return this->name;
}
void ConnectableSetConfiguration::setName(std::string_view const &name)
{
    this->name = name;
}
