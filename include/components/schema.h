#pragma once

#include "components/conf/schemaconfiguration.h"
#include "components/connection.h"
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
    unsigned getNewSchemaId()
    {
        return this->schemaId++;
    }
    unsigned getNewMachineId()
    {
        return this->machineId++;
    }
    unsigned getNewLinkId()
    {
        return this->linkId++;
    }
    unsigned getNewSwitchId()
    {
        return this->switchId++;
    }
    std::pair<unsigned, std::string> getNewSchemaBase()
    {
        unsigned newSchemaId = this->getNewSchemaId();
        return std::pair(newSchemaId, "Schema" + std::to_string(newSchemaId));
    }
    std::pair<unsigned, std::string> getNewMachineBase()
    {
        unsigned newMachineId = this->getNewMachineId();
        return std::pair(newMachineId,
                         "Machine" + std::to_string(newMachineId));
    }
    std::pair<unsigned, std::string> getNewLinkBase()
    {
        unsigned newLinkId = this->getNewLinkId();
        return std::pair(newLinkId, "Link" + std::to_string(newLinkId));
    }
    std::pair<unsigned, std::string> getNewSwitchBase()
    {
        unsigned newSwitchId = this->getNewSwitchId();
        return std::pair(newSwitchId, "Switch" + std::to_string(newSwitchId));
    }

private:
    unsigned schemaId  = 0;
    unsigned machineId = 0;
    unsigned linkId    = 0;
    unsigned switchId  = 0;
};

class Schema : public Connection
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

    std::map<unsigned, Link *>                   connectedLinks;
    std::map<unsigned, std::unique_ptr<Machine>> machines;
    std::map<unsigned, std::unique_ptr<Link>>    links;
    std::map<unsigned, std::unique_ptr<Schema>>  schemas;
    std::map<unsigned, std::unique_ptr<Switch>>  switches;

    void     drawItems();
    unsigned allocateNewMachine();
    unsigned allocateNewSwitch();
    unsigned allocateNewLink(LinkConnections connections);
    unsigned allocateNewSchema();
    void     deleteSchema(unsigned schemaId);
    void     deleteMachine(unsigned machineId);
    void     deleteLink(unsigned linkId);
    void     deleteSwitch(unsigned switchId);

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
