#include "components/schema.h"
#include "components/conf/machineconf.h"
#include "components/link.h"
#include "components/machine.h"
#include "icon/linkicon.h"
#include "icon/machineicon.h"
#include "icon/schemaicon.h"
#include <algorithm>
#include <memory>

Schema::Schema(const char *name, Schema *parent)
{
    this->name            = new std::string(name);
    this->machines        = std::map<unsigned, std::unique_ptr<Machine>>();
    this->links           = std::map<unsigned, std::unique_ptr<Link>>();
    this->schemas         = std::map<unsigned, std::unique_ptr<Schema>>();
    this->connected_links = std::map<unsigned, Link *>();
    this->window          = new SchemaWindow(this);

    if (parent) {
        schemaIds = parent->schemaIds;
    }
    else {
        schemaIds = new ids{0, 0, 0, 0};
    }

    this->id = schemaIds->schemaId;
    this->schemaIds->schemaId++;

    icon        = std::make_unique<SchemaIcon>(this->name->c_str(), this);
    icon->id    = this->id;
    icon->links = &this->connected_links;
    icon->setItem(this);
}

unsigned Schema::allocateNewMachine()
{
    const unsigned newMachineId = schemaIds->machineId;
    std::string    newMachineName("Machine" + std::to_string(newMachineId));
    auto           newMachine =
        std::make_unique<Machine>(this, newMachineId, newMachineName.c_str());

    machines.insert(std::pair(newMachineId, std::move(newMachine)));

    schemaIds->machineId++;

    return newMachineId;
}

unsigned Schema::allocateNewLink(LinkConnections connections)
{
    const unsigned newLinkId = schemaIds->linkId;
    std::string    newLinkName("Link" + std::to_string(newLinkId));

    auto newLink = std::make_unique<Link>(this, newLinkId, newLinkName.c_str(), connections);

    links.insert(std::pair(newLinkId, std::move(newLink)));

    schemaIds->linkId++;

    return newLinkId;
}

unsigned Schema::allocateNewSchema()
{
    const unsigned newSchemaId = schemaIds->schemaId;
    std::string    newSchemaName("Schema" + std::to_string(newSchemaId));
    auto newSchema = std::make_unique<Schema>(newSchemaName.c_str(), this);

    schemas.insert(std::pair(newSchemaId, std::move(newSchema)));

    return newSchemaId;
}

void Schema::deleteMachine(unsigned machineId)
{
    auto machineToDelete = this->machines.find(machineId);

    if (machineToDelete != this->machines.end()) {
        this->machines.erase(machineToDelete);
    }
}

void Schema::deleteSchema(unsigned schemaId)
{
    auto schemaToDelete = this->schemas.find(schemaId);

    if (schemaToDelete != this->schemas.end()) {
        this->schemas.erase(schemaToDelete);
    }
}

void Schema::deleteLink(unsigned linkId)
{
    auto linkToDelete = this->links.find(linkId);

    if (linkToDelete != this->links.end()) {
        this->links.erase(linkToDelete);
    }
}

void Schema::showConfiguration()
{
    this->window->show();
}

std::map<unsigned, Link *> *Schema::getConnectedLinks()
{
    return &this->connected_links;
}

SchemaIcon *Schema::getIcon()
{
    return this->icon.get();
}

void Schema::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connected_links = *map;
}

void Schema::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connected_links.find(link->id);

    if (linkToRemove != connected_links.end()) {
        this->connected_links.erase(linkToRemove);
    }
}
void Schema::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connected_links.find(link->id);

    if (linkToAdd == connected_links.end()) {
        this->connected_links.insert(std::pair(link->id, link));
    }
}
