#pragma once

#include "components/component.h"
#include "components/conf/linkconfiguration.h"
#include <memory>
#include <string>

class LinkIcon;
class LinkCloner;
class SchemaCloner;
class Connectable;
class Schema;

struct LinkConnections
{
    Connectable *begin;
    Connectable *end;
};

class Link
{
public:
    Link(Schema *schema, LinkConfiguration conf, LinkConnections connections);
    ~Link();

    void                        addLine();
    void                        draw();
    void                        showConfiguration();
    LinkIcon                   *getIcon();
    LinkConfiguration          *getConf();
    std::unique_ptr<LinkCloner> cloner(SchemaCloner *parent);

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<LinkIcon>          icon;
    std::unique_ptr<LinkConfiguration> conf;
};
