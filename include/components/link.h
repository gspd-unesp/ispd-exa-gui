#pragma once

#include <memory>
class LinkIcon;
class Icon;
class Item;
class Connection;
class Schema;

struct LinkConnections
{
    Connection *begin;
    Connection *end;
};

class Link
{
public:
    Link(Schema         *schema,
         unsigned        id,
         const char     *name,
         LinkConnections connections);
    ~Link();

    void addLine();
    void draw();

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<std::string> name;

    unsigned                  id;
    std::unique_ptr<LinkIcon> icon;
};
