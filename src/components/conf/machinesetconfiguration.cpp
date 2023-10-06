#include "components/conf/machinesetconfiguration.h"

MachineSetConfiguration::MachineSetConfiguration(std::string_view const &name) : name(name)
{
    this->latency = 0;
    this->bandwidth = 0;
    this->loadFactor = 0;
}

std::string MachineSetConfiguration::getName() const
{
    return this->name;
}

void MachineSetConfiguration::setName(std::string_view const &newName)
{
    this->name = newName;
}

unsigned MachineSetConfiguration::getBandwidth() const
{
    return this->bandwidth;
}
void MachineSetConfiguration::setBandwidth(const unsigned newBandwidth)
{
    this->bandwidth = newBandwidth;
}
double MachineSetConfiguration::getLatency() const
{
    return this->latency;
}
void MachineSetConfiguration::setLatency(const double newLatency)
{
    this->latency = newLatency;
}
double MachineSetConfiguration::getloadFactor() const
{
    return this->loadFactor;
}
void MachineSetConfiguration::setloadFactor(const double newloadFactor)
{
    this->loadFactor = newloadFactor;
}
