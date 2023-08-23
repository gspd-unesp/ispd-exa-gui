#pragma once

#include "components/conf/linkconfiguration.h"
#include "components/item.h"
#include <memory>
#include <string>

class LinkIcon;
class Connection;
class Schema;

struct LinkConnections
{
    Connection *begin;
    Connection *end;
};

class Link : public Item<LinkIcon>
{
public:
    Link(Schema *schema, LinkConfiguration *conf, LinkConnections connections);
    ~Link() override;

    void               addLine();
    void               draw();
    void               showConfiguration() override;
    LinkIcon          *getIcon() override;
    LinkConfiguration *getConf() override;

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<LinkIcon>          icon;
    std::unique_ptr<LinkConfiguration> conf;
};
