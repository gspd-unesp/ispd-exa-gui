#include "components/schema.h"
#include "components/cloner/schemacloner.h"
#include "components/conf/machineconfiguration.h"
#include "components/conf/schemaconfiguration.h"
#include "components/conf/switchconfiguration.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/switch.h"
#include "icon/linkicon.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/pixmappair.h"
#include "utils/iconPath.h"
#include "window/drawingtable/drawingtable.h"
#include "window/drawingtable/scene.h"
#include <QDebug>
#include <algorithm>
#include <iostream>
#include <memory>

Schema::Schema()
{
    this->window = std::make_unique<SchemaWindow>(this);
    this->ids    = new ComponentsIds;

    auto [firstSchemaId, firstSchemaName] = this->ids->getNewSchemaBase();
    this->conf =
        std::make_unique<SchemaConfiguration>(firstSchemaName, firstSchemaId);
}

Schema::Schema(Schema *parent, SchemaConfiguration *conf)
    : conf(conf), parent(parent)
{
    this->window = std::make_unique<SchemaWindow>(this);
    this->ids    = parent->ids;

    auto outputConfiguration = new SwitchConfiguration("", 0);
    this->outputSwitch = std::make_unique<Switch>(this, outputConfiguration);

    PixmapIconBuilder iconBuilder;
    this->icon = std::unique_ptr<PixmapIcon>(
        iconBuilder.setOwner(this)
            ->setPixmapPair(PixmapPair(schemaPath, schemaPathSelected))
            ->build());

    this->window->drawingTable->getScene()->addIcon(
        this->outputSwitch->getIcon());
}

Schema::~Schema()
{
    for (auto [linkId, link] : this->connectedLinks) {
        Connectable *otherIcon = (link->connections.begin == this)
                                     ? link->connections.end
                                     : link->connections.begin;

        otherIcon->removeConnectedLink(link);

        this->parent->deleteLink(linkId);
    }
}

unsigned Schema::allocateNewMachine()
{
    auto [newMachineId, newMachineName] = this->ids->getNewMachineBase();

    auto newMachineConf =
        new MachineConfiguration(newMachineName, newMachineId);

    auto newMachine = std::make_unique<Machine>(this, newMachineConf);

    this->connectables[newMachineId] = std::move(newMachine);

    return newMachineId;
}

unsigned Schema::allocateNewLink(LinkConnections connections)
{
    auto [newLinkId, newLinkName] = this->ids->getNewLinkBase();

    auto newLinkConf = new LinkConfiguration(newLinkName, newLinkId);

    auto newLink = std::make_unique<Link>(this, newLinkConf, connections);

    this->links[newLinkId] = std::move(newLink);

    return newLinkId;
}

unsigned Schema::allocateNewSchema()
{
    auto [newSchemaId, newSchemaName] = this->ids->getNewSchemaBase();

    auto newSchemaConf = new SchemaConfiguration(newSchemaName, newSchemaId);

    auto newSchema = std::make_unique<Schema>(this, newSchemaConf);

    this->connectables[newSchemaId] = std::move(newSchema);

    return newSchemaId;
}

unsigned Schema::allocateNewSwitch()
{
    auto [newSwitchId, newSwitchName] = this->ids->getNewSwitchBase();

    auto newSwitchConf = new SwitchConfiguration(newSwitchName, newSwitchId);

    auto newSwitch = std::make_unique<Switch>(this, newSwitchConf);

    this->connectables[newSwitchId] = std::move(newSwitch);

    return newSwitchId;
}

void Schema::deleteMachine(unsigned machineId)
{
    auto machineToDelete = this->connectables.find(machineId);

    if (machineToDelete != this->connectables.end()) {
        this->connectables.erase(machineToDelete);
    }
}

void Schema::deleteSchema(unsigned schemaId)
{
    auto schemaToDelete = this->connectables.find(schemaId);

    if (schemaToDelete != this->connectables.end()) {
        this->connectables.erase(schemaToDelete);
    }
}

void Schema::deleteSwitch(unsigned switchId)
{
    auto switchToDelete = this->connectables.find(switchId);

    if (switchToDelete != this->connectables.end()) {
        this->connectables.erase(switchToDelete);
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
    qDebug() << "Removing link of " << this->conf->getName().c_str();
    auto linkToRemove = this->connectedLinks.find(link->conf->getId());

    if (linkToRemove != connectedLinks.end()) {
        this->connectedLinks.erase(linkToRemove);
        qDebug() << "Removed link of " << this->conf->getName().c_str();
    }
}
void Schema::addConnectedLink(Link *link)
{
    qDebug() << "Adding link to " << this->conf->getName().c_str();
    auto linkToAdd = this->connectedLinks.find(link->conf->getId());

    if (linkToAdd == connectedLinks.end()) {
        this->connectedLinks[link->conf->getId()] = link;
    }
}

void Schema::drawItems()
{
    for (const auto &[id, connectable] : this->connectables) {
        this->window->drawingTable->getScene()->addIcon(
            connectable->getIcon(), connectable->getIcon()->scenePos());
    }
    for (const auto &[id, link] : this->links) {
        this->window->drawingTable->getScene()->addLink(link.get());
    }
}

SchemaConfiguration *Schema::getConf()
{
    return this->conf.get();
}

std::unique_ptr<ConnectableCloner> Schema::cloner(SchemaCloner *parent)
{
    return std::make_unique<SchemaCloner>(this, parent);
}

std::unique_ptr<std::vector<std::string>> Schema::print()
{
    auto stringVector = new std::vector<std::string>();
    stringVector->push_back(
        std::string("[" + std::to_string(this->conf->getId()) + "] = \"" +
                    this->conf->getName() + "\""));
    for (auto &[id, link] : this->connectedLinks) {
        stringVector->push_back(
            "|- [" + std::to_string(link->conf->getId()) + "] = " +
            std::to_string(link->connections.begin->getConf()->getId()) +
            " -> \"" + link->conf->getName() + "\" -> " +
            std::to_string(link->connections.end->getConf()->getId()));
    }
    for (auto &[id, connectable] : this->connectables) {
        auto connectableStrings = connectable->print();
        for (auto buffer : *connectableStrings.get()) {
            stringVector->push_back("|- " + buffer);
        }
    }

    return std::unique_ptr<std::vector<std::string>>(stringVector);
}

void Schema::print_as_root()
{
    auto buffers = this->print();
    for (auto buffer : *buffers.get()) {
        qDebug() << buffer.c_str();
    }
}
