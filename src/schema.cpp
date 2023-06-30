#include "schema.h"
#include "item/link.h"
#include "item/machineicon.h"
#include "item/schemaicon.h"
#include "load/linkload.h"
#include "load/machineload.h"

Schema::Schema(Schema *parent)
{
    machines = new std::map<unsigned, MachineLoad *>();
    links    = new std::map<unsigned, LinkLoad *>;
    schemas  = new std::map<unsigned, Schema *>;

    if (parent) {
        schemaIds = parent->schemaIds;
    }
    else {
        schemaIds = new ids{0, 0, 0, 0};
    }

    id = schemaIds->schemaId;
    schemaIds->schemaId++;
}

unsigned Schema::allocateNewMachine()
{
    const unsigned newMachineId = schemaIds->machineId;
    std::string    newMachineName("Machine" + std::to_string(newMachineId));
    auto          *newMachine = new MachineLoad(newMachineId);
    newMachine->icon          = new MachineIcon(newMachineName.c_str());

    machines->insert(
        std::pair<unsigned, MachineLoad *>(newMachineId, newMachine));

    schemaIds->machineId++;

    return newMachineId;
}

unsigned Schema::allocateNewLink()
{
    const unsigned newLinkId = schemaIds->linkId;
    std::string    newLinkName("Link" + std::to_string(newLinkId));
    auto          *newLink = new LinkLoad(newLinkId);
    newLink->line          = new Link(newLinkName.c_str());

    links->insert(std::pair<unsigned, LinkLoad *>(newLinkId, newLink));

    schemaIds->linkId++;

    return newLinkId;
}

unsigned Schema::allocateNewSchema()
{
    const unsigned newSchemaId = schemaIds->schemaId;
    std::string    newSchemaName("Schema" + std::to_string(newSchemaId));
    auto          *newSchema = new Schema(this);
    newSchema->icon          = new SchemaIcon(newSchemaName.c_str(), this);

    schemas->insert(std::pair<unsigned, Schema *>(newSchemaId, newSchema));

    return newSchemaId;
}
