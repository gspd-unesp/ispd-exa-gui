#include "components/schema.h"
#include "components/conf/machineconfiguration.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/switch.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/pixmappair.h"
#include "utils/iconPath.h"
#include "window/drawingtable/drawingtable.h"
#include <algorithm>
#include <memory>

Schema::Schema(const char *name, Schema *parent)
{
    this->name           = name;
    this->machines       = std::map<unsigned, std::unique_ptr<Machine>>();
    this->links          = std::map<unsigned, std::unique_ptr<Link>>();
    this->schemas        = std::map<unsigned, std::unique_ptr<Schema>>();
    this->switches       = std::map<unsigned, std::unique_ptr<Switch>>();
    this->connectedLinks = std::map<unsigned, Link *>();
    this->window         = std::make_unique<SchemaWindow>(this);

    if (parent) {
        schemaIds = parent->schemaIds;
    }
    else {
        schemaIds = new ids{0, 0, 0, 0};
    }

    this->id = schemaIds->schemaId;
    this->schemaIds->schemaId++;

    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setOwner(this)
            ->setPixmapPair(PixmapPair(schemaPath, schemaPathSelected))
            ->build());
}

Schema::~Schema()
{
    for (auto [linkId, link] : this->connectedLinks) {
        Connection *otherIcon = (link->connections.begin == this)
                                    ? link->connections.end
                                    : link->connections.begin;

        otherIcon->removeConnectedLink(link);

        this->deleteLink(linkId);
    }
}

unsigned Schema::allocateNewMachine()
{
    const unsigned newMachineId = schemaIds->machineId;
    std::string    newMachineName("Machine" + std::to_string(newMachineId));

    auto newMachineConf =
        new MachineConfiguration(newMachineName, newMachineId);

    machines[newMachineId] =
        std::make_unique<Machine>(this, newMachineConf);

    schemaIds->machineId++;

    return newMachineId;
}

unsigned Schema::allocateNewLink(LinkConnections connections)
{
    const unsigned newLinkId = schemaIds->linkId;
    std::string    newLinkName("Link" + std::to_string(newLinkId));

    auto newLink = std::make_unique<Link>(
        this, newLinkId, newLinkName.c_str(), connections);

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

unsigned Schema::allocateNewSwitch()
{
    const unsigned newSwitchId = schemaIds->switchId;
    std::string    newSwitchName("Switch" + std::to_string(newSwitchId));
    auto           newSwitch =
        std::make_unique<Switch>(this, newSwitchId, newSwitchName.c_str());

    this->switches.insert(std::pair(newSwitchId, std::move(newSwitch)));

    schemaIds->switchId++;

    return newSwitchId;
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

void Schema::deleteSwitch(unsigned switchId)
{
    auto switchToDelete = this->switches.find(switchId);

    if (switchToDelete != this->switches.end()) {
        this->switches.erase(switchToDelete);
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
    return &this->connectedLinks;
}

PixmapIcon *Schema::getIcon()
{
    return this->icon.get();
}

void Schema::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connectedLinks = *map;
}

void Schema::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connectedLinks.find(link->id);

    if (linkToRemove != connectedLinks.end()) {
        this->connectedLinks.erase(linkToRemove);
    }
}
void Schema::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connectedLinks.find(link->id);

    if (linkToAdd == connectedLinks.end()) {
        this->connectedLinks.insert(std::pair(link->id, link));
    }
}

void Schema::drawItems()
{
    std::vector<Connection *> machineVector;
    for (auto &it : this->machines) {
        machineVector.push_back(it.second.get());
    }
    this->window->drawingTable->addIcons(&machineVector);
}
