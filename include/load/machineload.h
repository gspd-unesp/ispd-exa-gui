#pragma once

#include "item/machineicon.h"
#include <string>

class MachineLoad
{
private:
    /**
     * It represents the computational power.
     */
    double computationalPower;

    /**
     * It represents the laod factor.
     */
    double loadFactor;

    /**
     * It represents the amount of memory RAM in
     * <em>gigabytes (GB)</em>.
     */
    double ram;

    /**
     * It represents the amount of hard disk in
     * <em>gigabytes (GB)</em>.
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

public:
    unsigned id;
    MachineLoad(unsigned id);
    MachineIcon *icon;
};
