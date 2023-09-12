#pragma once
#include "components/conf/switchconfiguration.h"
#include "components/connectable.h"
#include "icon/pixmapicon.h"

class Schema;

class Switch : public Connectable
{
public:
    Switch(Schema *schema, SwitchConfiguration *conf);
    ~Switch() override;
    std::map<unsigned, Link *> *getConnectedLinks() override;
    PixmapIcon                 *getIcon() override;
    SwitchConfiguration        *getConf() override;
    void setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(Link *link) override;
    void showConfiguration() override;
    std::unique_ptr<ConnectableCloner> cloner(SchemaCloner *parent) override;
    std::unique_ptr<std::vector<std::string>> print() override;
    std::string                               getName();

private:
    std::unique_ptr<SwitchConfiguration> conf;
    Schema                              *schema;
    std::map<unsigned, Link *>           connectedLinks;
    std::unique_ptr<PixmapIcon>          icon;
};
