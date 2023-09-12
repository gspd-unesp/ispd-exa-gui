#pragma once

#include <memory>
#include <string>

class Schema;
class Machine;
class PixmapIcon;
class MachineConfiguration;

class MachineBuilder
{
public:
    MachineBuilder();
    MachineBuilder          *setSchema(Schema *schema);
    MachineBuilder          *setConf(MachineConfiguration *conf);
    std::unique_ptr<Machine> build();

private:
    Schema               *schema;
    PixmapIcon           *icon;
    MachineConfiguration *conf;
};
