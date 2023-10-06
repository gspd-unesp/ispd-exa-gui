#pragma once

#include <memory>
#include <string>

class Schema;
class MachineSet;
class PixmapIcon;
class MachineSetConfiguration;

class ConnectableSetBuilder
{
public:
    ConnectableSetBuilder() = default;

    ConnectableSetBuilder *setSchema(Schema *baseSchema);
    ConnectableSetBuilder *setConf(MachineSetConfiguration const &baseConf);
    std::unique_ptr<MachineSet> build();

private:
    Schema                                      *schema;
    std::unique_ptr<MachineSetConfiguration> conf;
};
