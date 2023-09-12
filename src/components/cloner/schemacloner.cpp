#include "components/cloner/schemacloner.h"
#include "components/cloner/connectablecloner.h"
#include "components/cloner/linkcloner.h"
#include "components/cloner/switchcloner.h"
#include "components/conf/schemaconfiguration.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/schema.h"
#include "components/switch.h"
#include <algorithm>
#include <memory>
#include <optional>

SchemaCloner::SchemaCloner(Schema *base, SchemaCloner *parent) : parent(parent)
{
    this->setConnectables(base);
    qDebug() << "|- Created all cloners of schema.";
    this->clonedConf = std::make_unique<SchemaConfiguration>(*base->getConf());
    qDebug() << "|- Created all cloners of schema.";
}

std::unique_ptr<Connectable> SchemaCloner::clone(Schema *schema)
{
    qDebug() << "Begin to clone a schema.";
    auto [schemaId, schemaName] = schema->ids->getNewSchemaBase();

    qDebug()
        << "Begin to getting the schemaconfiguration of the cloned schema.";
    auto newClonedConf = new SchemaConfiguration(*this->clonedConf.get());
    newClonedConf->setId(schemaId);
    newClonedConf->setName(schemaName);

    qDebug() << "Creating the cloned Schema";
    auto clonedSchema = std::make_unique<Schema>(schema, newClonedConf);

    qDebug() << "Generating new connectables";
    this->generateConnectables(schema, clonedSchema.get());

    qDebug() << "Generating new links";

    clonedSchema->drawItems();

    qDebug() << "Returning the cloned schema.";

    return clonedSchema;
}

void SchemaCloner::generateConnectables(Schema *parent, Schema *cloned)
{
    ClonerAndConnectableVector vector;

    for (const auto &connectableCloner : this->connectableCloners) {

        auto newConnectable =
            std::unique_ptr<Connectable>(connectableCloner->clone(parent));

        vector.push_back(std::make_unique<ClonerAndConnectable>(
            newConnectable.get(), connectableCloner.get()));

        cloned->connectables[newConnectable->getConf()->getId()] =
            std::move(newConnectable);
    }

    this->generateLinks(parent, cloned, &vector);
}

void SchemaCloner::generateLinks(Schema                     *parent,
                                 Schema                     *cloned,
                                 ClonerAndConnectableVector *vector)
{
    for (const auto &linkCloner : this->linkCloners) {
        qDebug() << "Cloning a link";
        LinkConnections linkConnections{.begin = vector->getComponentFromCloner(
                                            linkCloner->connectionPair.begin),
                                        .end = vector->getComponentFromCloner(
                                            linkCloner->connectionPair.end)};
        qDebug() << "|- Created the link's linkConnections.";

        auto newLink = linkCloner->clone(parent, linkConnections);

        cloned->links[newLink->getConf()->getId()] = std::move(newLink);
        qDebug() << "|- Finished cloning a link";
    }
}

void SchemaCloner::setConnectables(const Schema *base)
{
    qDebug() << "Begin to create cloners Connectables of Schema.";

    std::vector<ClonerAndConnectable> linkConnectables;

    for (const auto &[id, connectable] : base->connectables) {
        auto newConnectableCloner = connectable->cloner(this);
        /*  */
        linkConnectables.push_back(ClonerAndConnectable(
            connectable.get(), newConnectableCloner.get()));
        /*  */
        this->connectableCloners.push_back(std::move(newConnectableCloner));
    }

    qDebug() << "|- Created Cloners of all Connetables of Schema.";
    this->setLinks(base, &linkConnectables);
    qDebug() << "|- End of creating Cloners of all Links of Schema.";
}

ConnectableCloner *getClonerFromComponent(
    std::vector<ClonerAndConnectable> *vector, const Connectable *component)
{

    if (auto rightIter = std::ranges::find_if(
            vector->begin(),
            vector->end(),
            [component](auto it) { return component == it.component; });
        rightIter != vector->end()) {
        return rightIter->cloner;
    }

    qDebug() << "Couldn't find the right cloner.";

    return nullptr;
}
Connectable *getComponentFromCloner(std::vector<ClonerAndConnectable> *vector,
                                    const ConnectableCloner           *cloner)
{
    if (auto rightIter = std::ranges::find_if(
            vector->begin(),
            vector->end(),
            [cloner](auto it) { return cloner == it.cloner; });
        rightIter != vector->end()) {
        return rightIter->component;
    }

    qDebug() << "Couldn't find the right component.";
    return nullptr;
}
void SchemaCloner::setLinks(const Schema                      *base,
                            std::vector<ClonerAndConnectable> *vector)
{
    qDebug() << "Begin to create Cloners of links of Schema.";

    qDebug() << "|- After getting names of connectables.";
    for (const auto &[id, link] : base->links) {
        std::unique_ptr<LinkCloner> newLinkCloner = link->cloner(this);

        newLinkCloner->connectionPair.begin =
            getClonerFromComponent(vector, link->connections.begin);
        newLinkCloner->connectionPair.end =
            getClonerFromComponent(vector, link->connections.end);

        this->linkCloners.push_back(std::move(newLinkCloner));
    }
    qDebug() << "|- After creating cloners of connectables.";

    qDebug() << "|- End of setLinks.";
}

std::vector<LinkCloner *> SchemaCloner::getConnectedLinkCloners()
{}

void SchemaCloner::addConnectedLink(LinkCloner *linkCloners)
{}
