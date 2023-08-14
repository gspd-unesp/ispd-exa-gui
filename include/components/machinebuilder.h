#pragma once

#include <string>

class Schema;
class Machine;
class PixmapIcon;
class MachineConfiguration;

class MachineBuilder
{
public:
    MachineBuilder();

    MachineBuilder *setSchema(Schema *schema);
    MachineBuilder *setIcon(PixmapIcon *icon);
    MachineBuilder *setConf(MachineConfiguration *conf);
    Machine        *build();

private:
    Schema               *schema;
    PixmapIcon          *icon;
    MachineConfiguration *conf;
};
