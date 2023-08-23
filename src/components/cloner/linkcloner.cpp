#include "components/link.h"
#include "components/cloner/linkcloner.h"
#include "components/cloner/schemacloner.h"

LinkCloner::LinkCloner(Link *base, SchemaCloner *parent) {
    this->base = base;
    this->parent = parent;
}
