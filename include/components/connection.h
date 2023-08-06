#pragma once
#include <map>
#include <memory>

class Link;
class Icon;

class Connection
{
public:
    virtual std::map<unsigned, Link *> *get_connected_links()        = 0;
    virtual Icon *getIcon() = 0;
    virtual void set_connectedLinks(std::map<unsigned, Link *> *map) = 0;
};
