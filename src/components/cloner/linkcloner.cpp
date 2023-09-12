#include "components/conf/linkconfiguration.h"
#include "components/link.h"
#include "components/cloner/linkcloner.h"
#include "components/cloner/schemacloner.h"
#include <vector>

LinkCloner::LinkCloner(Link *base, SchemaCloner *parent) {
    this->base = base;
    this->clonedConf = new LinkConfiguration(*base->getConf());
    this->parent = parent;
}

std::unique_ptr<Link> LinkCloner::clone(Schema *schema, LinkConnections linkConnections) {
    LinkConfiguration *newLinkConfiguration =
        new LinkConfiguration(*this->clonedConf);
    auto newLink = std::make_unique<Link>(schema, newLinkConfiguration, linkConnections);

    auto [newId, newName] = schema->ids->getNewLinkBase();
    newLink->getConf()->setId(newId);
    newLink->getConf()->setName(newName);
    return newLink;
}
