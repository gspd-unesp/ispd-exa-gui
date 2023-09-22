#include "components/cloner/linkcloner.h"
#include "components/cloner/schemacloner.h"
#include "components/conf/linkconfiguration.h"
#include "components/link.h"
#include <vector>

LinkCloner::LinkCloner(Link *base, SchemaCloner *parent)
    : clonedConf(*base->getConf()), base(base), parent(parent)
{}

std::shared_ptr<Link> LinkCloner::clone(Schema         *schema,
                                        LinkConnections linkConnections)
{
    LinkConfiguration newLinkConfiguration(this->clonedConf);
    auto              newLink =
        std::make_shared<Link>(schema, newLinkConfiguration, linkConnections);

    auto const [newId, newName] = schema->ids->getNewLinkBase();
    newLink->setId(newId);
    newLink->getConf()->setName(newName);
    return newLink;
}
