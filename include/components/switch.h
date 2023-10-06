#pragma once
#include "components/conf/switchconfiguration.h"
#include "components/connectable.h"
#include "icon/pixmapicon.h"
#include "window/switchconfigurationwindow.h"

class Schema;

class Switch : public Connectable
{
public:
    Switch(Schema *schema, SwitchConfiguration const &conf);
    ~Switch() override;
    std::vector<std::shared_ptr<Link>> *getConnectedLinks() override;
    PixmapIcon                         *getIcon() override;
    SwitchConfiguration                *getConf() override;
    void setConnectedLinks(std::vector<std::shared_ptr<Link>> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(std::shared_ptr<Link> link) override;
    void showConfiguration() override;
    std::unique_ptr<ConnectableCloner> cloner(SchemaCloner *parent) override;
    std::unique_ptr<std::vector<std::string>> print() override;
    std::string                               getName();

    unsigned getId() const override;
    void     setId(unsigned newId) override;

private:
    std::unique_ptr<SwitchConfigurationWindow> window;
    unsigned                                   id;
    std::unique_ptr<SwitchConfiguration>       conf;
    Schema                                    *schema;
    std::vector<std::shared_ptr<Link>>         connectedLinks;
    std::unique_ptr<PixmapIcon>                icon;
};
