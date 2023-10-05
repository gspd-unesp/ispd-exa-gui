#pragma once

#include "components/conf/schemaconfiguration.h"
#include "components/connectable.h"
#include "components/link.h"
#include "icon/pixmapicon.h"
#include "window/schemawindow.h"
#include "components/cloner/connectablecloner.h"
#include <map>
#include <memory>
#include <string>

struct LinkConnections;
class SchemaIcon;
class Link;
class Machine;
class Switch;

class ClonerContainer
{
public:
    ConnectableCloner *getCloner()
    {
        return this->cloner.get();
    }

    void setCloner(std::unique_ptr<ConnectableCloner> newCloner)
    {
        this->cloner = std::move(newCloner);
    }

    void freeCloner()
    {
        this->cloner.reset();
    }

private:
    std::unique_ptr<ConnectableCloner> cloner;
};

class ComponentsIds
{
public:
    unsigned getNewConnectableId()
    {
        return this->connectableId++;
    }
    unsigned getNewLinkId()
    {
        return this->linkId++;
    }

    std::pair<unsigned, std::string> getNewLinkBase()
    {
        unsigned newLinkId = this->getNewLinkId();
        return std::pair(newLinkId, "Link" + std::to_string(newLinkId));
    }

    std::pair<unsigned, std::string> getNewSchemaBase()
    {
        unsigned newSchemaId = this->getNewConnectableId();
        return std::pair(newSchemaId, "Schema" + std::to_string(newSchemaId));
    }

    std::pair<unsigned, std::string> getNewMachineBase()
    {
        unsigned newMachineId = this->getNewConnectableId();
        return std::pair(newMachineId,
                         "Machine" + std::to_string(newMachineId));
    }

    std::pair<unsigned, std::string> getNewSwitchBase()
    {
        unsigned newSwitchId = this->getNewConnectableId();
        return std::pair(newSwitchId, "Switch" + std::to_string(newSwitchId));
    }

    std::pair<unsigned, std::string> getNewSetBase()
    {
        unsigned newSetId = this->getNewConnectableId();
        return std::pair(newSetId, "Set" + std::to_string(newSetId));
    }

private:
    unsigned connectableId = 0;
    unsigned linkId        = 0;
};

class Schema : public Connectable
{
public:
    Schema();
    Schema(Schema *parent, SchemaConfiguration const &conf);
    Schema(Schema &schema);
    ~Schema();

    Schema(Schema &&)                                              = default;
    Schema                                   &operator=(Schema &&) = default;
    std::unique_ptr<PixmapIcon>               icon;
    std::unique_ptr<SchemaWindow>             window;
    std::vector<std::shared_ptr<Link>>        connectedLinks;
    std::map<unsigned, std::shared_ptr<Link>> links;
    std::map<unsigned, std::unique_ptr<Connectable>> connectables;
    std::unique_ptr<Switch>                          outputSwitch;
    void                                             drawItems();
    unsigned                                         allocateNewMachine();
    unsigned                                         allocateNewSet();
    unsigned                                         allocateNewSwitch();
    unsigned allocateNewLink(LinkConnections connections);
    unsigned allocateNewSchema();

    std::unique_ptr<ConnectableCloner>  cloner(SchemaCloner *parent) override;
    std::vector<std::shared_ptr<Link>> *getConnectedLinks() override;
    void                                setConnectedLinks(
                                       std::vector<std::shared_ptr<Link>> *linksVector) override;
    void                 removeConnectedLink(Link *link) override;
    void                 addConnectedLink(std::shared_ptr<Link> link) override;
    void                 showConfiguration() override;
    PixmapIcon          *getIcon() override;
    SchemaConfiguration *getConf() override;
    ComponentsIds       *ids;
    void                 print_as_root();
    std::unique_ptr<std::vector<std::string>> print() override;

    unsigned getId() const override;
    void     setId(unsigned newId) override;
    std::shared_ptr<ClonerContainer>   cloneContainer;

private:
    unsigned                             id;
    std::unique_ptr<SchemaConfiguration> conf;
    Schema                              *parent;
};
