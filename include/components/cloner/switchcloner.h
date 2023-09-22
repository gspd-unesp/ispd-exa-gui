#pragma once

#include "components/cloner/connectablecloner.h"
#include "components/conf/switchconfiguration.h"

class Switch;
class SchemaCloner;
class Connectable;

class SwitchCloner : public ConnectableCloner
{
public:
    SwitchCloner(Switch *base, SchemaCloner *parent);
    std::unique_ptr<Connectable> clone(Schema *schema) override;
    std::vector<LinkCloner *>    getConnectedLinkCloners() override;
    void                      addConnectedLink(LinkCloner *linkCloner) override;
    std::vector<LinkCloner *> linkCloners;

private:
    std::unique_ptr<SwitchConfiguration> clonedConf;
    QPointF                              pos;
    SchemaCloner                        *parent;
};
