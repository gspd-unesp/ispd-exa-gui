#pragma once

#include "components/schema.h"
#include "components/cloner/cloner.h"
#include <algorithm>
#include <map>
#include <memory>
#include <optional>

class Machine;
class Link;
class Switch;
class MachineCloner;
class LinkCloner;
class SwitchCloner;

class SchemaCloner : public Cloner<Schema>
{
public:
    explicit SchemaCloner(Schema *base, SchemaCloner *parent = nullptr);
    std::unique_ptr<Schema> clone(Schema *schema) override;

private:
    void setSchemas();
    void setMachines();
    void setLinks();
    void setSwitches();

    void generateMachines(
        std::map<unsigned, std::unique_ptr<Machine>> &machines);
    void generateSchemas(std::map<unsigned, std::unique_ptr<Schema>> &schemas);
    void generateLinks(std::map<unsigned, std::unique_ptr<Link>> &links);
    void generateSwitches(
        std::map<unsigned, std::unique_ptr<Switch>> &switches);

    std::vector<std::unique_ptr<MachineCloner>> machines;
    std::vector<std::unique_ptr<SchemaCloner>>  schemas;
    std::vector<std::unique_ptr<LinkCloner>>    links;
    std::vector<std::unique_ptr<SwitchCloner>>  switches;

    Schema                    *base;
    SchemaCloner              *parent;
    std::unique_ptr<Schema>    schemeClone;
    std::map<unsigned, Link *> connectedLinks;
};
