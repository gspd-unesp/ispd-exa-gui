#pragma once

#include "components/conf/machineconfiguration.h"
#include <memory>
#include <string>

class Schema;
class Machine;
class PixmapIcon;
class MachineConfiguration;

class MachineBuilder
{
public:
    MachineBuilder() = default;

    MachineBuilder          *setSchema(Schema *baseSchema);
    MachineBuilder          *setConf(MachineConfiguration const &baseConf);
    std::unique_ptr<Machine> build();

private:
    Schema                               *schema;
    std::unique_ptr<MachineConfiguration> conf;
};
