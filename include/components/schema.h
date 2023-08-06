#pragma once

#include "components/connection.h"
#include "components/machine.h"
#include "window/schemawindow.h"
#include <map>

class SchemaIcon;
class Link;
class Machine;

typedef struct IDS
{
    unsigned schemaId;
    unsigned machineId;
    unsigned linkId;
    unsigned switchId;
} ids;

class Schema : public Item, public Connection
{
public:
    ids *schemaIds;
    Schema(const char *name, Schema *parent = nullptr);

    Schema(const Schema &)                 = default;
    Schema(Schema &&)                      = default;
    Schema      &operator=(const Schema &) = default;
    Schema      &operator=(Schema &&)      = default;
    unsigned     id;
    SchemaIcon  *icon;
    std::string *name;

    SchemaWindow *window;

    std::map<unsigned, Link *>    *connected_links;
    std::map<unsigned, Machine *> *machines;
    std::map<unsigned, Link *>    *links;
    std::map<unsigned, Schema *>  *schemas;

    unsigned allocateNewMachine();
    unsigned allocateNewLink();
    unsigned allocateNewSchema();
    void     deleteMachine(unsigned machineId);
    void     deleteLink(unsigned linkId);

    void                        showConfiguration() override;
    std::map<unsigned, Link *> *get_connected_links() override;
    Icon                       *getIcon() override;
    void set_connectedLinks(std::map<unsigned, Link *> *map) override;
};
