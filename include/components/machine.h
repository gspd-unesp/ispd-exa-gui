#pragma once

#include <map>
#include <string>
#include <vector>

#include "components/connection.h"
#include "components/item.h"
#include "icon/machineicon.h"

class MachineLoad;
class Schema;
class Link;

class Machine : public Connection
{
public:
    Machine(Schema *schema, unsigned id, const char *name);
    Machine(Machine &machine);
    virtual ~Machine();

    std::map<unsigned, Link *> *getConnectedLinks() override;
    void setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(Link *link) override;
    std::unique_ptr<Machine> clone();

    void  showConfiguration() override;
    MachineIcon *getIcon() override;

    std::string                  name;
    std::map<unsigned, Link *>   connected_links;
    Schema                      *schema;
    MachineLoad                 *load;
    std::unique_ptr<MachineIcon> icon;
    unsigned                     id;
};
