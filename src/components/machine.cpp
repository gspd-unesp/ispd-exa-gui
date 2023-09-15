#include "components/machine.h"
#include "components/cloner/machinecloner.h"
#include "components/conf/itemconfiguration.h"
#include "components/conf/machineconfiguration.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/machineiconfactory.h"
#include "icon/pixmapicon.h"
#include "window/machineconfigurationwindow.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

Machine::Machine(Schema *schema, MachineConfiguration *conf)
    : schema(schema), conf(std::make_unique<MachineConfiguration>(*conf))
{
    this->icon =
        std::unique_ptr<PixmapIcon>(MachineIconFactory().iconBuilder(this));

    this->window = std::make_unique<MachineConfigurationWindow>(this->conf->getName().c_str());
}

Machine::~Machine()
{
    qDebug() << "Deleting machine";
    for (auto [linkId, link] : this->connectedLinks) {
        this->schema->links.erase(linkId);
    }
    qDebug() << "|- End of destructor of machine.";
}

void Machine::showConfiguration()
{
    this->window->show();
}

PixmapIcon *Machine::getIcon()
{
    return this->icon.get();
}

std::map<unsigned, Link *> *Machine::getConnectedLinks()
{
    return &this->connectedLinks;
}

void Machine::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connectedLinks = *map;
}

void Machine::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connectedLinks.find(link->conf->getId());

    if (linkToRemove != connectedLinks.end()) {
        this->connectedLinks.erase(linkToRemove);
    }
}

void Machine::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connectedLinks.find(link->conf->getId());

    if (linkToAdd == connectedLinks.end()) {
        this->connectedLinks.insert(std::pair(link->conf->getId(), link));
    }
}

ItemConfiguration *Machine::getConf()
{
    return this->conf.get();
}

std::unique_ptr<std::vector<std::string>> Machine::print()
{
    auto buffer  = std::string("[" + std::to_string(this->conf->getId()) +
                              "] = \"" + this->conf->getName() + "\"");
    auto buffers = new std::vector<std::string>();
    buffers->push_back(buffer);
    for (auto &[id, link] : this->connectedLinks) {
        buffers->push_back(
            "|- [" + std::to_string(link->conf->getId()) + "] = " +
            std::to_string(link->connections.begin->getConf()->getId()) +
            " -> \"" + link->conf->getName() + "\" -> " +
            std::to_string(link->connections.end->getConf()->getId()));
    }

    return std::unique_ptr<std::vector<std::string>>(buffers);
}

std::unique_ptr<ConnectableCloner> Machine::cloner(SchemaCloner *parent)
{
    return std::make_unique<MachineCloner>(this, parent);
}
