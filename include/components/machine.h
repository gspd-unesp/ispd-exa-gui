#pragma once

#include <map>
#include <string>
#include <vector>

#include "components/connection.h"

class Schema;
class Link;
class Icon;
class Cloner;
class ItemConfiguration;
class MachineConfiguration;

class Machine : public Connectable
{
public:
    Machine(Schema *schema, MachineConfiguration *conf);
    ~Machine();

    std::map<unsigned, Link *> *getConnectedLinks() override;

    void setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(Link *link) override;

    void               showConfiguration() override;
    PixmapIcon        *getIcon() override;
    ItemConfiguration *getConf() override;
    Cloner            *cloner();

    std::map<unsigned, Link *> connected_links;

    Schema                               *schema;
    std::unique_ptr<MachineConfiguration> conf;
    std::unique_ptr<PixmapIcon>           icon;
};
