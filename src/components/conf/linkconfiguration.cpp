#include "components/conf/linkconfiguration.h"
#include <QDebug>

LinkConfiguration::LinkConfiguration(std::string name, unsigned id)
    : id(id), name(name)
{}

LinkConfiguration::~LinkConfiguration() {
    qDebug() << "LinkConfiguration is being deleted";
}

unsigned LinkConfiguration::getId()
{
    return this->id;
}
std::string LinkConfiguration::getName()
{
    return this->name;
}

void LinkConfiguration::setId(unsigned id)
{
    this->id = id;
}
void LinkConfiguration::setName(std::string name)
{
    this->name = name;
}
