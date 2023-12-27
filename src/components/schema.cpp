#include "components/schema.h"
#include "components/cloner/schemacloner.h"
#include "components/conf/machineconfiguration.h"
#include "components/conf/machinesetconfiguration.h"
#include "components/conf/schemaconfiguration.h"
#include "components/conf/switchconfiguration.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/machinebuilder.h"
#include "components/machineset.h"
#include "components/machinesetbuilder.h"
#include "components/switch.h"
#include "icon/pixmapiconbuilder.h"
#include "utils/iconPath.h"
#include "window/drawingtable/drawingtable.h"
#include "window/drawingtable/scene.h"
#include <QDebug>
#include <memory>

Schema::Schema()
{
    this->window         = std::make_unique<SchemaWindow>(this);
    this->ids            = new ComponentsIds;
    this->cloneContainer = std::make_shared<ClonerContainer>();

    auto [firstSchemaId, firstSchemaName] = this->ids->getNewSchemaBase();
    this->id                              = firstSchemaId;
    this->conf = std::make_unique<SchemaConfiguration>(firstSchemaName);
}

Schema::Schema(Schema *parent, SchemaConfiguration const &conf)
    : ids(parent->ids), cloneContainer(parent->cloneContainer),
      conf(std::make_unique<SchemaConfiguration>(conf)), parent(parent)
{
    this->window = std::make_unique<SchemaWindow>(this);

    SwitchConfiguration outputConfiguration("");
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
    for (auto const &link : this->connectedLinks) {
        qDebug() << link.use_count();
        auto otherConnectable =
            link.get()->connections.getOtherConnectable(this);

        otherConnectable->removeConnectedLink(link.get());
        this->parent->links.erase(link.get()->getId());
    }
}

unsigned Schema::allocateNewSet()
{
    auto [newSetId, newSetName] = this->ids->getNewSetBase();

    MachineSetConfiguration newSetConf(newSetName);
    auto                    newSet =
        ConnectableSetBuilder().setConf(newSetConf)->setSchema(this)->build();
    newSet->setId(newSetId);

    this->connectables[newSetId] = std::move(newSet);

    return newSetId;
}

unsigned Schema::allocateNewMachine()
{
    auto [newMachineId, newMachineName] = this->ids->getNewMachineBase();

    MachineConfiguration newMachineConf(newMachineName);
    auto                 newMachine =
        MachineBuilder().setConf(newMachineConf)->setSchema(this)->build();
    newMachine->setId(newMachineId);

    this->connectables[newMachineId] = std::move(newMachine);

    return newMachineId;
}

unsigned Schema::allocateNewLink(LinkConnections connections)
{
    auto [newLinkId, newLinkName] = this->ids->getNewLinkBase();

    LinkConfiguration newLinkConf(newLinkName);
    auto newLink = std::make_shared<Link>(this, newLinkConf, connections);
    newLink->setId(newLinkId);

    auto [a, b] = connections;
    a->addConnectedLink(newLink);
    b->addConnectedLink(newLink);

    this->links[newLinkId] = std::move(newLink);

    return newLinkId;
}

unsigned Schema::allocateNewSchema()
{
    auto [newSchemaId, newSchemaName] = this->ids->getNewSchemaBase();

    SchemaConfiguration newSchemaConf(newSchemaName);

    auto newSchema = std::make_unique<Schema>(this, newSchemaConf);
    newSchema->setId(newSchemaId);

    this->connectables[newSchemaId] = std::move(newSchema);

    return newSchemaId;
}

unsigned Schema::allocateNewSwitch()
{
    auto [newSwitchId, newSwitchName] = this->ids->getNewSwitchBase();

    SwitchConfiguration newSwitchConf(newSwitchName);

    auto newSwitch = std::make_unique<Switch>(this, newSwitchConf);
    newSwitch->setId(newSwitchId);

    this->connectables[newSwitchId] = std::move(newSwitch);

    return newSwitchId;
}

void Schema::showConfiguration()
{
    this->window->show();
}
std::vector<std::shared_ptr<Link>> *Schema::getConnectedLinks()
{
    return &this->connectedLinks;
}

PixmapIcon *Schema::getIcon()
{
    return this->icon.get();
}

void Schema::setConnectedLinks(std::vector<std::shared_ptr<Link>> *map)
{
    this->connectedLinks = *map;
}

void Schema::removeConnectedLink(Link *link)
{
    qDebug() << "Removing link of " << this->conf->getName().c_str();

    std::erase_if(this->connectedLinks,
                  [link](auto iter) { return iter.get() == link; });
}
void Schema::addConnectedLink(std::shared_ptr<Link> link)
{
    qDebug() << "Adding link to " << this->conf->getName().c_str();

    this->connectedLinks.push_back(link);
}

void Schema::drawItems()
{
    for (const auto &[connectableId, connectable] : this->connectables) {
        this->window->drawingTable->getScene()->addIcon(
            connectable->getIcon(), connectable->getIcon()->scenePos());
    }
    for (const auto &[linkId, link] : this->links) {
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
    stringVector->push_back(std::string("[" + std::to_string(this->getId()) +
                                        "] = \"" + this->conf->getName() +
                                        "\""));
    for (auto &link : this->connectedLinks) {
        stringVector->push_back(
            "|- [" + std::to_string(link->getId()) +
            "] = " + std::to_string(link->connections.begin->getId()) +
            " -> \"" + link->conf->getName() + "\" -> " +
            std::to_string(link->connections.end->getId()));
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

    for (auto const &buffer : *buffers.get()) {
        qDebug() << buffer.c_str();
    }
}

unsigned Schema::getId() const
{
    return this->id;
}

void Schema::setId(unsigned newId)
{
    this->id = newId;
}

void to_json(json &j, const Schema &s)
{
    j["users"]     = json::array();
    j["workloads"] = json::array();
    j["services"]  = {{"machines", json::array()},
                      {"masters", json::array()},
                      {"links", json::array()},
                      {"switches", json::array()}};
    for (auto &i : s.connectables) {
        if (auto machine = dynamic_cast<Machine *>(i.second.get());
            machine != nullptr) {
            if (machine->conf->master) {
                j["services"]["masters"].push_back(*machine);
            }
            else {
                j["services"]["machines"].push_back(*machine);
            }
        }
        else if (auto switchC = dynamic_cast<Switch *>(i.second.get());
                 switchC != nullptr) {
            j["services"]["switches"].push_back(*switchC);
        }
        /* } else if (auto schema = static_cast<Schema*>(i.second.get()) !=
         * nullptr) { */
        /*     j["services"]["machines"].push_back(); */
        /* } */
    }

    for (auto &i : s.links) {
        j["services"]["links"].push_back(*i.second.get());
    }
}
