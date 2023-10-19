#include "components/machineset.h"
#include "components/cloner/connectablecloner.h"
#include "components/conf/machinesetconfiguration.h"
#include "components/link.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include "icon/seticonfactory.h"
#include <memory>
#include <vector>

MachineSet::MachineSet(Schema *schema, MachineSetConfiguration *conf)
    : schema(schema), conf(std::make_unique<MachineSetConfiguration>(*conf))
{
    this->icon =
        std::unique_ptr<PixmapIcon>(SetIconFactory().iconBuilder(this));
    this->window =
        std::make_unique<MachineSetConfigurationWindow>(this->conf.get());
}

MachineSet::~MachineSet()
{
    qDebug() << "Deleting set";

    for (auto const &link : this->connectedLinks) {
        qDebug() << link.use_count();
        auto otherConnectable =
            link.get()->connections.getOtherConnectable(this);

        otherConnectable->removeConnectedLink(link.get());
        this->schema->links.erase(link.get()->getId());
    }
    qDebug() << "|- End of destructor of set.";
}

std::vector<std::shared_ptr<Link>> *MachineSet::getConnectedLinks()
{
    return &this->connectedLinks;
}
void MachineSet::setConnectedLinks(
    std::vector<std::shared_ptr<Link>> *linksVector)
{
    this->connectedLinks = *linksVector;
}
void MachineSet::removeConnectedLink(Link *link)
{
    std::erase_if(this->connectedLinks,
                  [link](auto iter) { return iter.get() == link; });
}

void MachineSet::addConnectedLink(std::shared_ptr<Link> link)
{
    this->connectedLinks.push_back(link);
}

PixmapIcon *MachineSet::getIcon()
{
    return this->icon.get();
}

unsigned MachineSet::getId() const
{
    return this->id;
}

void MachineSet::setId(unsigned newId)
{
    this->id = newId;
}

std::unique_ptr<std::vector<std::string>> MachineSet::print()
{
    return std::make_unique<std::vector<std::string>>();
}

std::unique_ptr<ConnectableCloner> MachineSet::cloner(SchemaCloner *parent)
{
    return nullptr;
}

void MachineSet::showConfiguration()
{
    this->window->show();
}

ItemConfiguration *MachineSet::getConf()
{
    return this->conf.get();
}
