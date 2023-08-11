#include "components/cloner/schemacloner.h"
#include "components/cloner/machinecloner.h"
#include "components/cloner/linkcloner.h"
#include "components/cloner/switchcloner.h"
#include "components/schema.h"
#include "components/switch.h"
#include "components/machine.h"
#include "components/link.h"
#include <memory>

SchemaCloner::SchemaCloner(Schema *base, SchemaCloner *parent)
{
    this->base = base;
    this->parent = parent;
}

std::unique_ptr<Schema> SchemaCloner::clone()
{
    std::unique_ptr<Schema> clonedSchema = std::make_unique<Schema>("");

    this->generateMachines(clonedSchema->machines);
    this->generateSchemas(clonedSchema->schemas);
    this->generateSwitches(clonedSchema->switches);
    this->generateLinks(clonedSchema->links);

    return clonedSchema;
}

void SchemaCloner::generateMachines(std::map<unsigned, std::unique_ptr<Machine>> &machines)
{
}

void SchemaCloner::generateSchemas(std::map<unsigned, std::unique_ptr<Schema>> &schemas)
{
}

void SchemaCloner::generateLinks(std::map<unsigned, std::unique_ptr<Link>> &links)
{}

void SchemaCloner::generateSwitches(std::map<unsigned, std::unique_ptr<Switch>> &switches)
{}

void SchemaCloner::setMachines(std::map<unsigned, std::unique_ptr<Machine>> baseMachines)
{
    unsigned key = 0;
    auto it = baseMachines.begin();
    while (it != baseMachines.end()) {
        this->machines.insert(std::pair(key, std::make_unique<MachineCloner>(it->second.get(), this)));

        key++;
    }
}

void SchemaCloner::setSchemas(std::map<unsigned, std::unique_ptr<Schema>> baseSchemas)
{
    unsigned key = 0;
    auto it = baseSchemas.begin();
    while (it != baseSchemas.end()) {
        this->schemas.insert(std::pair(key, std::make_unique<SchemaCloner>(it->second.get(), this)));

        key++;
    }
}

void SchemaCloner::setLinks(std::map<unsigned, std::unique_ptr<Link>> baseLinks)
{
    unsigned key = 0;
    auto it = baseLinks.begin();
    while (it != baseLinks.end()) {
        this->links.insert(std::pair(key, std::make_unique<LinkCloner>(it->second.get(), this)));

        key++;
    }
}

void SchemaCloner::setSwitches(std::map<unsigned, std::unique_ptr<Switch>> baseSwitches)
{
    unsigned key = 0;
    auto it = baseSwitches.begin();
    while (it != baseSwitches.end()) {
        this->switches.insert(std::pair(key, std::make_unique<SwitchCloner>(it->second.get(), this)));

        key++;
    }
}
