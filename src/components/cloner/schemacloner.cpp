#include "components/cloner/schemacloner.h"
#include "components/cloner/linkcloner.h"
#include "components/cloner/machinecloner.h"
#include "components/cloner/switchcloner.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/schema.h"
#include "components/switch.h"
#include <algorithm>
#include <memory>

SchemaCloner::SchemaCloner(Schema *base, SchemaCloner *parent)
{
    this->base   = base;
    this->parent = parent;
    this->setMachines();
}

std::unique_ptr<Item> SchemaCloner::clone()
{
    qDebug() << "Begin to clone a schema.";
    auto clonedSchema = std::make_unique<Schema>(*this->base);
    clonedSchema->id  = this->base->schemaIds->schemaId++;

    qDebug() << "Generating new schema machines.";
    this->generateMachines(clonedSchema->machines);
    for (auto const &it : clonedSchema->machines) {
        qDebug() << "MACHINE FROM CLONED SCHEMA " << it.second->id;
    }
    clonedSchema->drawItems();

    qDebug() << "Generating new schema schemas.";
    /* this->generateSchemas(clonedSchema->schemas); */
    qDebug() << "Generating new schema switches.";
    /* this->generateSwitches(clonedSchema->switches); */
    qDebug() << "Generating new schema links.";
    /* this->generateLinks(clonedSchema->links); */

    qDebug() << "Returning the cloned schema.";

    return clonedSchema;
}

void SchemaCloner::generateMachines(
    std::map<unsigned, std::unique_ptr<Machine>> &machines)
{
    for (auto &it : this->machines) {
        std::unique_ptr<Item> newMachine = it->clone();
        unsigned              id = static_cast<Machine *>(newMachine.get())->id;
        machines.insert(id, std::move(newMachine));
    }
    qDebug() << "Ended generating new schema machines.";
}

void SchemaCloner::generateSchemas(
    std::map<unsigned, std::unique_ptr<Schema>> &schemas)
{}

void SchemaCloner::generateLinks(
    std::map<unsigned, std::unique_ptr<Link>> &links)
{}

void SchemaCloner::generateSwitches(
    std::map<unsigned, std::unique_ptr<Switch>> &switches)
{}

void SchemaCloner::setMachines()
{
    for (auto &it : this->base->machines) {
        this->machines.push_back(
            std::make_unique<MachineCloner>(it.second.get(), this));
    }
}

void SchemaCloner::setSchemas()
{
    for (auto &it : this->base->schemas) {

        this->schemas.push_back(
            std::make_unique<SchemaCloner>(it.second.get(), this));
    }
}

void SchemaCloner::setLinks()
{
    for (auto &it : this->base->links) {
        this->links.push_back(
            std::make_unique<LinkCloner>(it.second.get(), this));
    }
}

void SchemaCloner::setSwitches()
{
    for (auto &it : this->base->switches) {
        this->switches.push_back(
            std::make_unique<SwitchCloner>(it.second.get(), this));
    }
}
