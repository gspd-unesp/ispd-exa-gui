#pragma once

#include "components/cloner/connectablecloner.h"
#include "components/conf/schemaconfiguration.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include <algorithm>
#include <map>
#include <memory>
#include <optional>

class Machine;
class Link;
class Switch;
class MachineCloner;
class LinkCloner;
class SwitchCloner;
class Connectable;

class SchemaCloner : public ConnectableCloner
{
public:
    explicit SchemaCloner(Schema *base, SchemaCloner *parent = nullptr);
    Connectable *clone(Schema *schema) override;

private:
    void setConnectables(Schema *base);
    void setLinks(Schema *base);

    void generateConnectables(
        std::map<unsigned, std::unique_ptr<Connectable>> &Connectables);
    void generateLinks(std::map<unsigned, std::unique_ptr<Link>> &links);

    Schema                              *base;
    SchemaCloner                        *parent;
    std::unique_ptr<Schema>              schemeClone;
    std::map<unsigned, Link *>           connectedLinks;
    std::unique_ptr<SchemaConfiguration> clonedConf;
    std::vector<std::tuple<unsigned, LinkCloner *, unsigned>> connections;
    std::vector<std::unique_ptr<ConnectableCloner>> connectableCloners;
    std::vector<std::unique_ptr<LinkCloner>>        linkCloners;
};
