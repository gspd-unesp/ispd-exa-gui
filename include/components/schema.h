#pragma once

#include "components/conf/schemaconfiguration.h"
#include "components/connectable.h"
#include "components/link.h"
#include "icon/pixmapicon.h"
#include "window/schemawindow.h"
#include <map>
#include <memory>
#include <string>

struct LinkConnections;
class SchemaIcon;
class Link;
class Machine;
class Switch;

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

private:
    unsigned connectableId = 0;
    unsigned linkId        = 0;
};

class Schema : public Connectable
{
public:
    Schema();
    Schema(Schema *parent, SchemaConfiguration *conf);
    Schema(Schema &schema);
    ~Schema();

    Schema(Schema &&)                                = default;
    Schema                     &operator=(Schema &&) = default;
    std::unique_ptr<PixmapIcon> icon;

    std::unique_ptr<SchemaWindow> window;

    std::map<unsigned, Link *> connectedLinks;

    std::map<unsigned, std::unique_ptr<Link>>        links;
    std::map<unsigned, std::unique_ptr<Connectable>> connectables;

    void     drawItems();
    unsigned allocateNewMachine();
    unsigned allocateNewSwitch();
    unsigned allocateNewLink(LinkConnections connections);
    unsigned allocateNewSchema();
    void     deleteSchema(unsigned schemaId);
    void     deleteMachine(unsigned machineId);
    void     deleteLink(unsigned linkId);
    void     deleteSwitch(unsigned switchId);

    Cloner                     *cloner() override;
    void                        showConfiguration() override;
    std::map<unsigned, Link *> *getConnectedLinks() override;
    PixmapIcon                 *getIcon() override;
    SchemaConfiguration        *getConf() override;
    void           setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void           removeConnectedLink(Link *link) override;
    void           addConnectedLink(Link *link) override;
    ComponentsIds *ids;

private:
    std::unique_ptr<SchemaConfiguration> conf;
    Schema                              *parent;
};
