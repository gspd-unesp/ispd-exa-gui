#include "components/conf/linkconfiguration.h"
#include <QDebug>

LinkConfiguration::LinkConfiguration(std::string_view const name) : name(name)
{
    this->latency = 0;
    this->bandwidth = 0;
    this->loadFactor = 0;
}

std::string LinkConfiguration::getName() const
{
    return this->name;
}

void LinkConfiguration::setName(std::string_view const newName)
{
    this->name = newName;
}

unsigned LinkConfiguration::getBandwidth() const
{
    return this->bandwidth;
}
void LinkConfiguration::setBandwidth(const unsigned newBandwidth)
{
    this->bandwidth = newBandwidth;
}
double LinkConfiguration::getLatency() const
{
    return this->latency;
}
void LinkConfiguration::setLatency(const double newLatency)
{
    this->latency = newLatency;
}
double LinkConfiguration::getloadFactor() const
{
    return this->loadFactor;
}
void LinkConfiguration::setloadFactor(const double newloadFactor)
{
    this->loadFactor = newloadFactor;
}
