#pragma once

#include "components/connection.h"
#include "components/link.h"
#include "components/machine.h"
#include "icon/schemaicon.h"
#include "window/schemawindow.h"
#include <map>
#include <memory>

struct LinkConnections;
class SchemaIcon;
class Link;
class Machine;
class Switch;

typedef struct IDS
{
    unsigned schemaId;
    unsigned machineId;
    unsigned linkId;
    unsigned switchId;
} ids;

class Schema : public Connection
{
public:
    ids *schemaIds;
    explicit Schema(const char *name, Schema *parent = nullptr);
    Schema(Schema &schema);

    Schema(Schema &&)                                = default;
    Schema                     &operator=(Schema &&) = default;
    unsigned                    id;
    std::unique_ptr<SchemaIcon> icon;
    std::string                 name;

    std::unique_ptr<SchemaWindow> window;

    std::map<unsigned, Link *>                   connected_links;
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
    SchemaIcon                 *getIcon() override;
    void setConnectedLinks(std::map<unsigned, Link *> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(Link *link) override;
};
