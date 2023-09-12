#pragma once

#include "components/cloner/cloner.h"
#include "components/connectable.h"
#include "icon/pixmapicon.h"

class LinkCloner;
class Schema;

class ConnectableCloner
{
public:
    virtual std::unique_ptr<Connectable> clone(Schema *schema = nullptr) = 0;
    virtual ~ConnectableCloner()                                 = default;
    virtual std::vector<LinkCloner *> getConnectedLinkCloners()  = 0;
    virtual void addConnectedLink(LinkCloner *linkCloner)        = 0;
};
