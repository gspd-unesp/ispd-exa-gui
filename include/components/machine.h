#pragma once

#include <map>
#include <string>
#include <vector>

#include "components/connection.h"
#include "components/item.h"

class MachineLoad;
class MachineIcon;
class Schema;
class Link;

class Machine : public Item, public Connection
{
public:
    Machine(Schema *schema, unsigned id, const char *name);
    virtual ~Machine();

    std::map<unsigned, Link *> *get_connected_links()        override;
    void set_connectedLinks(std::map<unsigned, Link *> *map) override;

    void  showConfiguration() override;
    Icon *getIcon() override;

    std::map<unsigned, Link *> *connected_links;
    Schema                     *schema;
    MachineLoad                *load;
    MachineIcon                *icon;
    unsigned                    id;
};
