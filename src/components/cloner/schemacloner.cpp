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

SchemaCloner::SchemaCloner(Schema *base, SchemaCloner *parent)
{
    this->parent = parent;
    this->setConnectables(base);
    this->setLinks(base);
    this->clonedConf = std::unique_ptr<SchemaConfiguration>(
        new SchemaConfiguration(*base->getConf()));
}

Connectable *SchemaCloner::clone(Schema *schema)
{
    qDebug() << "Begin to clone a schema.";
    auto [schemaId, schemaName] = schema->ids->getNewSchemaBase();

    qDebug()
        << "Begin to getting the schemaconfiguration of the cloned schema.";
    auto newClonedConf = new SchemaConfiguration(*this->clonedConf.get());
    newClonedConf->setId(schemaId);
    newClonedConf->setName(schemaName);

    qDebug() << "Creating the cloned Schema";
    auto clonedSchema = new Schema(schema, newClonedConf);

    qDebug() << "Generating new connectables";
    this->generateConnectables(clonedSchema->connectables);
    qDebug() << "Generating new links";
    this->generateLinks(clonedSchema->links);

    clonedSchema->drawItems();

    qDebug() << "Returning the cloned schema.";

    return clonedSchema;
}

void SchemaCloner::generateConnectables(
    std::map<unsigned, std::unique_ptr<Connectable>> &connectables)
{}

void SchemaCloner::generateLinks(
    std::map<unsigned, std::unique_ptr<Link>> &links)
{}

void SchemaCloner::setLinks(Schema *base)
{}

void SchemaCloner::setConnectables(Schema *base)
{
    for (auto &[connectableId, connectable] : base->connectables) {
        auto newConnectableCloner = std::unique_ptr<ConnectableCloner>(
            static_cast<ConnectableCloner *>(connectable->cloner()));
        this->connectableCloners.push_back(std::move(newConnectableCloner));

        for (auto &[linkId, link] : *connectable->getConnectedLinks()) {
            auto newLinkCloner = std::unique_ptr<LinkCloner>(
                static_cast<LinkCloner *>(connectable->cloner()));

            auto otherConnectable = link->connections.begin == connectable.get()
                                        ? link->connections.end
                                        : link->connections.begin;
            auto otherConnectableId = otherConnectable->getConf()->getId();
            auto otherConnectableCloner =
                static_cast<ConnectableCloner *>(otherConnectable->cloner());

            this->connections.push_back(
                std::tuple<unsigned, LinkCloner *, unsigned>(
                    connectableId, newLinkCloner.get(), otherConnectableId));

            this->linkCloners.push_back(std::move(newLinkCloner));
            this->connectableCloners.push_back(
                std::unique_ptr<ConnectableCloner>(otherConnectableCloner));
        }
    }
}
