#include "components/schema.h"
#include "components/conf/machineconf.h"
#include "components/link.h"
#include "components/machine.h"
#include "icon/linkicon.h"
#include "icon/machineicon.h"
#include "icon/schemaicon.h"

Schema::Schema(const char *name, Schema *parent)
{
    this->name            = new std::string(name);
    this->machines        = new std::map<unsigned, Machine *>();
    this->links           = new std::map<unsigned, Link *>;
    this->schemas         = new std::map<unsigned, Schema *>;
    this->connected_links = new std::map<unsigned, Link *>;
    this->window          = new SchemaWindow(this);

    if (parent) {
        schemaIds = parent->schemaIds;
    }
    else {
        schemaIds = new ids{0, 0, 0, 0};
    }

    this->id = schemaIds->schemaId;
    this->schemaIds->schemaId++;

    icon        = new SchemaIcon(this->name->c_str(), this);
    icon->id    = this->id;
    icon->links = this->connected_links;
    icon->setItem(this);
}

unsigned Schema::allocateNewMachine()
{
    const unsigned newMachineId = schemaIds->machineId;
    std::string    newMachineName("Machine" + std::to_string(newMachineId));
    auto *newMachine = new Machine(this, newMachineId, newMachineName.c_str());

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
    auto          *newSchema = new Schema(newSchemaName.c_str(), this);

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

void Schema::showConfiguration()
{
    this->window->show();
}

std::map<unsigned, Link *> *Schema::get_connected_links()
{
    return this->connected_links;
}

Icon *Schema::getIcon()
{
    return this->icon;
}

void Schema::set_connectedLinks(std::map<unsigned, Link *> *map)
{
    this->connected_links = map;
}
