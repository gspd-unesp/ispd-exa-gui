#pragma once

#include "components/cloner/connectablecloner.h"
#include "components/cloner/linkcloner.h"
#include "components/conf/schemaconfiguration.h"
#include "components/schema.h"
#include <algorithm>
#include <map>
#include <memory>
#include <optional>

class Machine;
class Link;
class Switch;
class MachineCloner;
class SwitchCloner;
class Connectable;

class ClonerAndConnectable
{
public:
    ClonerAndConnectable(Connectable *component, ConnectableCloner *cloner)
        : cloner(cloner), component(component)
    {}
    explicit ClonerAndConnectable(Connectable *component) : component(component)
    {}
    explicit ClonerAndConnectable(ConnectableCloner *cloner) : cloner(cloner)
    {}

    ConnectableCloner *cloner;
    Connectable       *component;
};

class ClonerAndConnectableVector
    : public std::vector<std::unique_ptr<ClonerAndConnectable>>
{
public:
    ConnectableCloner *getClonerFromComponent(const Connectable *component)
    {

        if (auto rightIter = std::ranges::find_if(
                this->begin(),
                this->end(),
                [component](auto &it) { return component == it->component; });
            rightIter != this->end()) {
            return rightIter->get()->cloner;
        }

        qDebug() << "Couldn't find the right cloner.";

        return nullptr;
    }
    Connectable *getComponentFromCloner(const ConnectableCloner *cloner)
    {
        if (auto rightIter = std::ranges::find_if(
                this->begin(),
                this->end(),
                [cloner](auto &it) { return cloner == it->cloner; });
            rightIter != this->end()) {
            return rightIter->get()->component;
        }

        qDebug() << "Couldn't find the right component.";
        return nullptr;
    }
};

class SchemaCloner : public ConnectableCloner
{
public:
    explicit SchemaCloner(Schema *base, SchemaCloner *parent = nullptr);
    std::unique_ptr<Connectable> clone(Schema *schema = nullptr) override;

private:
    void setConnectables(const Schema *base);
    void setLinks(const Schema                      *base,
                  std::vector<ClonerAndConnectable> *vector);

    std::vector<LinkCloner *> getConnectedLinkCloners() override;
    void addConnectedLink(LinkCloner *linkCloners) override;

    void generateConnectables(Schema *parent, Schema *cloned);
    void generateLinks(Schema                     *parent,
                       Schema                     *cloned,
                       ClonerAndConnectableVector *vector);
    void workPath(
        Connectable *connectable,
        std::vector<std::tuple<Connectable *, ConnectableCloner *, bool>>
            alreadyClonedConnectables);

    SchemaCloner                                             *parent;
    std::unique_ptr<Schema>                                   schemeClone;
    std::map<unsigned, Link *>                                connectedLinks;
    std::unique_ptr<SchemaConfiguration>                      clonedConf;
    std::vector<std::tuple<unsigned, LinkCloner *, unsigned>> connections;
    std::vector<std::unique_ptr<ConnectableCloner>> connectableCloners;
    std::vector<std::unique_ptr<LinkCloner>>        linkCloners;
};
