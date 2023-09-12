#include "components/cloner/switchcloner.h"
#include "components/cloner/schemacloner.h"
#include "components/conf/switchconfiguration.h"
#include "components/connectable.h"
#include "components/connectable.h"
#include "components/switch.h"
#include "components/switchbuilder.h"

SwitchCloner::SwitchCloner(Switch *base, SchemaCloner *parent)
    : pos(base->getIcon()->scenePos()), parent(parent)
{
    this->clonedConf = std::make_unique<SwitchConfiguration>(*base->getConf());
}

std::unique_ptr<Connectable> SwitchCloner::clone(Schema *schema)
{
    qDebug() << "Before Cloning a machine";
    auto *newSwitchConfiguration =
        new SwitchConfiguration(*this->clonedConf);
    auto newSwitch = SwitchBuilder()
                              .setSchema(schema)
                              ->setConf(newSwitchConfiguration)
                              ->build();

    newSwitch->getIcon()->setPos(this->pos);

    auto [newId, newName] = schema->ids->getNewSwitchBase();
    newSwitch->getConf()->setId(newId);
    newSwitch->getConf()->setName(newName);

    qDebug() << "Returning a cloned machine...";
    return newSwitch;
}
std::vector<LinkCloner *> SwitchCloner::getConnectedLinkCloners() {
    return this->linkCloners;
}
void SwitchCloner::addConnectedLink(LinkCloner *linkCloner) {
    this->linkCloners.push_back(linkCloner);
}
