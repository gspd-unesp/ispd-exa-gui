#pragma once

class Link;
class SchemaCloner;

class LinkCloner {
public:
    LinkCloner(Link *base, SchemaCloner *parent);
private:
    Link *base;
};
