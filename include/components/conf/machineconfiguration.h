#pragma once
#include "components/conf/itemconfiguration.h"
#include <string>
#include <vector>

class MachineConfiguration : public ItemConfiguration
{
public:
    MachineConfiguration(std::string name, unsigned id);
    MachineConfiguration(MachineConfiguration &conf) = default;

    std::string getName();
    void        setName(std::string name);
    unsigned    getId();
    void        setId(unsigned id);

private:
    std::string name;
    unsigned    id;
    /**
     * It represents the computational power.
     */
    double computationalPower;

    /**
     * It represents the laod factor.
     */
    double loadFactor;

    /**
     * It represents the amount of memory RAM in gigabytes (GB)
     */
    double ram;

    /**
     * It represents the amount of hard disk in gigabytes (GB).
     */
    double hardDisk;

    /**
     * It represents the energy consumption.
     */
    double energyConsumption;

    /**
     * It represents the cost per processing.
     */
    double costPerProcessing;

    /**
     * It represents the cost per memory.
     */
    double costPerMemory;

    /**
     * It represents the cost per disk.
     */
    double costPerDisk;

    /**
     * It represents the amount of cores in the chip.
     */
    int coreCount;

    /**
     * It represents if this machine acts as master, that is,
     * if this variable is {@code true}, then this machine
     * is a master; otherwise {@code false}.
     */
    bool master;

    /**
     * It represents the owner.
     */
    std::string owner;

    /**
     * It contains the scheduling algorithm used.
     */
    std::string schedulingAlgorithm;
};
