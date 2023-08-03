#pragma once

#include <map>
#include <string>
#include <vector>

#include "item/item.h"

class MachineLoad;
class MachineIcon;
class Schema;
class Link;

class Machine : public Item
{
public:
    Machine(Schema *schema, unsigned id, const char *name);
    ~Machine();

    void  showConfiguration();
    Icon *getIcon();

    std::map<unsigned, Link *> *links;
    Schema                     *schema;
    MachineLoad                *load;
    MachineIcon                *icon;
    unsigned                    id;
};
