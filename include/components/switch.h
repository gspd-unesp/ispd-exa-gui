#pragma once
#include "components/connection.h"
#include "icon/switchicon.h"

class Schema;

class Switch : public Connection
{
public:
    Switch(Schema *schema, unsigned id, const char *name);
    ~Switch();
    std::map<unsigned, Link *> *getConnectedLinks() override;
    SwitchIcon                 *getIcon() override;
    void        setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void        removeConnectedLink(Link *link) override;
    void        addConnectedLink(Link *link) override;
    void        showConfiguration() override;
    std::string getName();

private:
    Schema                     *schema;
    std::string                 name;
    unsigned                    id;
    std::map<unsigned, Link *>  connectedLinks;
    std::unique_ptr<SwitchIcon> icon;
};
