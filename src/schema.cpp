#include "schema.h"
#include "item/link.h"
#include "item/linkicon.h"
#include "item/machine.h"
#include "item/machineicon.h"
#include "item/schemaicon.h"
#include "load/machineload.h"

Schema::Schema(Schema *parent)
{
    machines = new std::map<unsigned, Machine *>();
    links    = new std::map<unsigned, Link *>;
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
    auto          *newMachine = new Machine(this, newMachineId, newMachineName.c_str());

    machines->insert(std::pair<unsigned, Machine *>(newMachineId, newMachine));

    schemaIds->machineId++;

    return newMachineId;
}

unsigned Schema::allocateNewLink()
{
    const unsigned newLinkId = schemaIds->linkId;
    std::string    newLinkName("Link" + std::to_string(newLinkId));

    auto *newLink     = new Link(newLinkId);
    newLink->icon     = new LinkIcon(newLinkName.c_str());
    newLink->icon->id = newLinkId;

    links->insert(std::pair<unsigned, Link *>(newLinkId, newLink));

    schemaIds->linkId++;

    return newLinkId;
}

unsigned Schema::allocateNewSchema()
{
    const unsigned newSchemaId = schemaIds->schemaId;
    std::string    newSchemaName("Schema" + std::to_string(newSchemaId));
    auto          *newSchema = new Schema(this);
    newSchema->icon          = new SchemaIcon(newSchemaName.c_str(), this);
    newSchema->icon->id      = newSchemaId;

    schemas->insert(std::pair<unsigned, Schema *>(newSchemaId, newSchema));

    return newSchemaId;
}

void Schema::deleteMachine(unsigned machineId)
{
    Machine *machineToDelete = this->machines->at(machineId);

    delete (machineToDelete);

    this->machines->erase(machineId);
}

void Schema::deleteLink(unsigned linkId)
{
    Link *linkToDelete = this->links->at(linkId);

    delete (linkToDelete);

    this->links->erase(linkId);
}

Icon *Schema::getIcon()
{
    return this->icon;
}

void Schema::showConfiguration()
{
}
