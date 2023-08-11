#include <algorithm>
#include <map>
#include <memory>
#include <optional>

class Schema;
class Machine;
class Link;
class Switch;
class MachineCloner;
class LinkCloner;
class SwitchCloner;

class SchemaCloner
{
public:
    explicit SchemaCloner(Schema *base, SchemaCloner *parent = nullptr);
    std::unique_ptr<Schema> clone();

private:
    void setMachines(std::map<unsigned, std::unique_ptr<Machine>> baseMachines);
    void setSchemas(std::map<unsigned, std::unique_ptr<Schema>> baseSchemas);
    void setLinks(std::map<unsigned, std::unique_ptr<Link>> baseLinks);
    void setSwitches(std::map<unsigned, std::unique_ptr<Switch>> baseSwitches);

    void generateMachines(std::map<unsigned, std::unique_ptr<Machine>> &machines);
    void generateSchemas(std::map<unsigned, std::unique_ptr<Schema>> &schemas);
    void generateLinks(std::map<unsigned, std::unique_ptr<Link>> &links);
    void generateSwitches(std::map<unsigned, std::unique_ptr<Switch>> &switches);

    std::map<unsigned, std::unique_ptr<MachineCloner>> machines;
    std::map<unsigned, std::unique_ptr<SchemaCloner>>  schemas;
    std::map<unsigned, std::unique_ptr<LinkCloner>>    links;
    std::map<unsigned, std::unique_ptr<SwitchCloner>>  switches;

    Schema *base;
    SchemaCloner *parent;
    std::unique_ptr<Schema> schemeClone;
    std::map<unsigned, Link*> connectedLinks;
};
