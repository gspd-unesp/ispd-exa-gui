#include "components/conf/linkconfiguration.h"
#include <QDebug>

LinkConfiguration::LinkConfiguration(std::string_view const name)
    : name(name)
{}

std::string LinkConfiguration::getName() const
{
    return this->name;
}

void LinkConfiguration::setName(std::string_view const newName)
{
    this->name = newName;
}
