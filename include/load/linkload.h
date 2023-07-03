#pragma once

class Link;
class LinkLoad
{
public:
    LinkLoad(unsigned id);
    ~LinkLoad();
    unsigned id;
    Link    *line;
};
