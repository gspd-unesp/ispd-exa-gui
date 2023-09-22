#pragma once

#include "components/cloner/cloner.h"
#include "components/cloner/connectablecloner.h"
#include "components/component.h"
#include "components/conf/linkconfiguration.h"
#include "components/link.h"

class SchemaCloner;

struct ConnectableClonerPair
{
    ConnectableCloner *begin;
    ConnectableCloner *end;
};

class LinkCloner
{
public:
    LinkCloner(Link *base, SchemaCloner *parent);
    std::shared_ptr<Link> clone(Schema         *schema,
                                LinkConnections linkConnections);
    ConnectableClonerPair connectionPair;

private:
    LinkConfiguration clonedConf;
    Link             *base;
    SchemaCloner     *parent;
};
