#include "components/cloner/linkcloner.h"
#include "components/cloner/schemacloner.h"
#include "components/conf/linkconfiguration.h"
#include "components/link.h"
#include <vector>

LinkCloner::LinkCloner(Link *base, SchemaCloner *parent)
    : clonedConf(*base->getConf())
{
    this->base   = base;
    this->parent = parent;
}

std::unique_ptr<Link> LinkCloner::clone(Schema         *schema,
                                        LinkConnections linkConnections)
{
    LinkConfiguration newLinkConfiguration =
        LinkConfiguration(this->clonedConf);
    auto newLink =
        std::make_unique<Link>(schema, newLinkConfiguration, linkConnections);

    auto [newId, newName] = schema->ids->getNewLinkBase();
    newLink->getConf()->setId(newId);
    newLink->getConf()->setName(newName);
    return newLink;
}
