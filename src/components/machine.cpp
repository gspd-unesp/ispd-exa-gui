#include "components/machine.h"
#include "components/conf/linkconf.h"
#include "components/conf/machineconfiguration.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/machineiconfactory.h"
#include "icon/pixmapicon.h"
#include "window/machineconfigurationwindow.h"
#include <map>
#include <memory>
#include <vector>

Machine::Machine(Schema *schema, MachineConfiguration *conf) : connected_links()
{
    this->conf = std::unique_ptr<MachineConfiguration>(conf);
    this->icon =
        std::unique_ptr<PixmapIcon>(MachineIconFactory().iconBuilder(this));
    this->schema = schema;
}

Machine::~Machine()
{
    for (auto [linkId, link] : this->connected_links) {
        Connection *otherIcon = (link->connections.begin == this)
                                    ? link->connections.end
                                    : link->connections.begin;

        otherIcon->removeConnectedLink(link);

        this->schema->deleteLink(linkId);
    }

    qDebug() << "Deleting " << this->conf->getName().c_str();
}

void Machine::showConfiguration()
{
    MachineConfigurationWindow *machineIconConfig =
        new MachineConfigurationWindow(this->conf->getName().c_str());
    machineIconConfig->show();
}

PixmapIcon *Machine::getIcon()
{
    return this->icon.get();
}

std::map<unsigned, Link *> *Machine::getConnectedLinks()
{
    return &this->connected_links;
}

void Machine::setConnectedLinks(std::map<unsigned, Link *> *map)
{
    this->connected_links = *map;
}

void Machine::removeConnectedLink(Link *link)
{
    auto linkToRemove = this->connected_links.find(link->id);

    if (linkToRemove != connected_links.end()) {
        this->connected_links.erase(linkToRemove);
    }
}

void Machine::addConnectedLink(Link *link)
{
    auto linkToAdd = this->connected_links.find(link->id);

    if (linkToAdd == connected_links.end()) {
        this->connected_links.insert(std::pair(link->id, link));
    }
}
