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

    this->window = std::make_unique<MachineConfigurationWindow>(this->conf.get());
}

Machine::~Machine()
{
    qDebug() << "Deleting machine";

    for (auto const &link : this->connectedLinks) {
        qDebug() << link.use_count();
        auto otherConnectable =
            link.get()->connections.getOtherConnectable(this);

        otherConnectable->removeConnectedLink(link.get());
        this->schema->links.erase(link.get()->getId());
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

std::vector<std::shared_ptr<Link>> *Machine::getConnectedLinks()
{
    return &this->connectedLinks;
}

void Machine::setConnectedLinks(std::vector<std::shared_ptr<Link>> *linkVector)
{
    this->connectedLinks = *linkVector;
}

void Machine::removeConnectedLink(Link *link)
{
    qDebug() << "Begin to delete a connected link from machine " << this->id;

    std::erase_if(this->connectedLinks,
                  [link](auto iter) { return iter.get() == link; });
}

void Machine::addConnectedLink(std::shared_ptr<Link> link)
{
    this->connectedLinks.push_back(link);
}

ItemConfiguration *Machine::getConf()
{
    return this->conf.get();
}

std::unique_ptr<std::vector<std::string>> Machine::print()
{
    auto buffer  = std::string("[" + std::to_string(this->getId()) + "] = \"" +
                              this->conf->getName() + "\"");
    auto buffers = new std::vector<std::string>();
    buffers->push_back(buffer);
    for (auto &link : this->connectedLinks) {
        buffers->push_back("|- [" + std::to_string(link->getId()) + "] = " +
                           std::to_string(link->connections.begin->getId()) +
                           " -> \"" + link->conf->getName() + "\" -> " +
                           std::to_string(link->connections.end->getId()));
    }

    return std::unique_ptr<std::vector<std::string>>(buffers);
}

std::unique_ptr<ConnectableCloner> Machine::cloner(SchemaCloner *parent)
{
    return std::make_unique<MachineCloner>(this, parent);
}

unsigned Machine::getId() const
{
    return this->id;
}

void Machine::setId(unsigned newId)
{
    this->id = newId;
}
