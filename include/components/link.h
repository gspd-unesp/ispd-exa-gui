#pragma once

#include "components/conf/linkconfiguration.h"
#include "components/component.h"
#include <memory>
#include <string>

class LinkIcon;
class Connectable;
class Schema;

struct LinkConnections
{
    Connectable *begin;
    Connectable *end;
};

class Link : public Component
{
public:
    Link(Schema *schema, LinkConfiguration *conf, LinkConnections connections);
    ~Link() override;

    void               addLine();
    void               draw();
    void               showConfiguration() override;
    Icon              *getIcon() override;
    LinkConfiguration *getConf() override;
    Cloner            *cloner() override;

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<LinkIcon>          icon;
    std::unique_ptr<LinkConfiguration> conf;
};
