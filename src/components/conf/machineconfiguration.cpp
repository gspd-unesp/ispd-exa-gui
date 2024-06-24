#include "components/conf/machineconfiguration.h"

MachineConfiguration::MachineConfiguration(std::string_view const &name)
    : name(name)
{
    this->master = false;
    this->scheduler = "RoundRobin";
    this->gpuPower = 1.0;
    this->gpuInterconnectionBandwidth = 1.0;
    this->gpuCoreCount = 1;
    this->wattageMax = 1;
    this->wattageIdle = 1;
    this->loadFactor = 0.1;
    this->ram = 1;
    this->coreCount = 1;
    this->computationalPower = 1;
    this->energyConsumption = 1.0;
    this->costPerDisk = 1.0;
    this->costPerMemory = 1.0;
    this->costPerProcessing = 1.0;
    this->hardDisk = 1.0;
    this->isDynamic = false;
}

std::string MachineConfiguration::getName() const 
{
    return this->name;
}

void MachineConfiguration::setName(std::string_view const &newName)
{
    this->name = newName;
}

void to_json(json &j, const MachineConfiguration &m) {
    if (m.master) {
        j = json{
            {"scheduler", m.scheduler},
            {"slaves", m.slaves},
            {"isDynamic", m.isDynamic}
        };
    } else {
        j = json{
            {"power", m.computationalPower},
            {"load", m.loadFactor},
            {"core_count", m.coreCount},
            {"gpu_power", m.gpuPower},
            {"gpu_core_count", m.gpuCoreCount},
            {"gpu_interconnection_bandwidth", m.gpuInterconnectionBandwidth},
            {"wattage_idle", m.wattageIdle},
            {"wattage_max", m.wattageMax},
        };
    }
}
