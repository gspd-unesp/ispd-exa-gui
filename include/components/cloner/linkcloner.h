#pragma once

#include "components/cloner/cloner.h"
#include "components/link.h"

class SchemaCloner;

class LinkCloner : public Cloner
{
public:
    LinkCloner(Link *base, SchemaCloner *parent);
    Link *clone(Schema *schema) override;

private:
    Link         *base;
    SchemaCloner *parent;
};
