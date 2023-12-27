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

unsigned SwitchConfiguration::getBandwidth() const
{
    return this->bandwidth;
}
void SwitchConfiguration::setBandwidth(const unsigned newBandwidth)
{
    this->bandwidth = newBandwidth;
}
double SwitchConfiguration::getLatency() const
{
    return this->latency;
}
void SwitchConfiguration::setLatency(const double newLatency)
{
    this->latency = newLatency;
}
double SwitchConfiguration::getloadFactor() const
{
    return this->loadFactor;
}
void SwitchConfiguration::setloadFactor(const double newloadFactor)
{
    this->loadFactor = newloadFactor;
}

void to_json(json &j, const SwitchConfiguration &sc) {
    j["bandwidth"] = sc.getBandwidth();
    j["load"] = sc.getloadFactor();
    j["latency"] = sc.getLatency();
}
