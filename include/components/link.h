#pragma once

class LinkIcon;
class Icon;
class Item;
class Connection;

class Link
{
public:
    Link(unsigned id);
    ~Link();

    void addLine(Connection *a, Connection *b);
    void draw();

    Connection *begin;
    Connection *end;

    unsigned  id;
    LinkIcon *icon;
};
