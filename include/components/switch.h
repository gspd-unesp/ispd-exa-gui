#pragma once
#include "components/conf/switchconfiguration.h"
#include "components/connection.h"
#include "icon/pixmapicon.h"

class Schema;

class Switch : public Connection
{
public:
    Switch(Schema *schema, unsigned id, const char *name);
    ~Switch() override;
    std::map<unsigned, Link *> *getConnectedLinks() override;
    PixmapIcon                 *getIcon() override;
    SwitchConfiguration        *getConf() override;
    void        setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void        removeConnectedLink(Link *link) override;
    void        addConnectedLink(Link *link) override;
    void        showConfiguration() override;
    std::string getName();

private:
    std::unique_ptr<SwitchConfiguration> conf;
    Schema                              *schema;
    std::string                          name;
    unsigned                             id;
    std::map<unsigned, Link *>           connectedLinks;
    std::unique_ptr<PixmapIcon>          icon;
};
