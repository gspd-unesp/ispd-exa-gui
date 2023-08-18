#pragma once
#include "components/conf/switchconfiguration.h"
#include "components/connection.h"
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
    void        setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void        removeConnectedLink(Link *link) override;
    void        addConnectedLink(Link *link) override;
    void        showConfiguration() override;
    Cloner     *cloner() override;
    std::string getName();

private:
    std::unique_ptr<SwitchConfiguration> conf;
    Schema                              *schema;
    std::map<unsigned, Link *>           connectedLinks;
    std::unique_ptr<PixmapIcon>          icon;
};
