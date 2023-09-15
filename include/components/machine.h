#pragma once

#include <map>
#include <string>
#include <vector>

#include "components/connectable.h"
#include "window/machineconfigurationwindow.h"

class Schema;
class SchemaCloner;
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
    std::unique_ptr<std::vector<std::string>> print() override;

    void                               showConfiguration() override;
    PixmapIcon                        *getIcon() override;
    ItemConfiguration                 *getConf() override;
    std::unique_ptr<ConnectableCloner> cloner(
        SchemaCloner *parent = nullptr) override;

    std::map<unsigned, Link *> connectedLinks;

    Schema *schema;

    std::unique_ptr<MachineConfiguration> conf;
    std::unique_ptr<PixmapIcon>           icon;

private:
    std::unique_ptr<MachineConfigurationWindow> window;
};
