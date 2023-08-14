#include "components/conf/machineconfiguration.h"

MachineConfiguration::MachineConfiguration(std::string name, unsigned id)
{
    this->name = name;
    this->id   = id;
}

std::string MachineConfiguration::getName() {
    return this->name;
}
unsigned    MachineConfiguration::getId() {
    return this->id;
}

