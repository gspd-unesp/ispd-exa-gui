#pragma once

class LinkIcon;
class Icon;
class Item;

class Link
{
public:
    Link(unsigned id);
    ~Link();

    void addLine(Item *a, Item *b);

    Item *begin;
    Item *end;

    unsigned  id;
    LinkIcon *icon;
};
