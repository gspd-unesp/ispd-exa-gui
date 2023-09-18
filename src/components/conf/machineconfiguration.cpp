#include "components/conf/machineconfiguration.h"

MachineConfiguration::MachineConfiguration(std::string_view const &name)
    : name(name)
{
}

std::string MachineConfiguration::getName() const 
{
    return this->name;
}

void MachineConfiguration::setName(std::string_view const &newName)
{
    this->name = newName;
}
