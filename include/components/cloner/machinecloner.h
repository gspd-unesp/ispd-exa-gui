#pragma once

#include "components/cloner/connectablecloner.h"
#include "icon/pixmapicon.h"
#include "qpoint.h"
#include <memory>

class MachineConfiguration;
class SchemaCloner;
class Schema;
class Machine;

class MachineCloner : public ConnectableCloner
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent = nullptr);
    std::unique_ptr<Connectable> clone(Schema *schema) override;
    std::vector<LinkCloner *>    getConnectedLinkCloners() override;
    void addConnectedLink(LinkCloner *linkCloner) override;

private:
    std::unique_ptr<MachineConfiguration> clonedConf;
    QPointF                               pos;
    SchemaCloner                         *parent;
    std::vector<LinkCloner *>             linkCloners;
};
