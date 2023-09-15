#include "components/cloner/machinecloner.h"
#include "components/conf/machineconfiguration.h"
#include "components/machine.h"
#include "components/machinebuilder.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include <memory>
#include <string>

MachineCloner::MachineCloner(Machine *base, SchemaCloner *parent)
    : pos(base->getIcon()->scenePos()), parent(parent)
{
    qDebug() << "Before copying machine conf.";
    this->clonedConf = std::make_unique<MachineConfiguration>(*base->conf);
    qDebug() << "Before getting machineIcon scenePos.";
    qDebug() << "After constructor of machineCloner;";
}

std::unique_ptr<Connectable> MachineCloner::clone(Schema *schema)
{
    qDebug() << "Before Cloning a machine";
    auto newMachineConfiguration =
        std::make_unique<MachineConfiguration>(*this->clonedConf);
    auto newMachine = MachineBuilder()
                          .setSchema(schema)
                          ->setConf(std::move(newMachineConfiguration))
                          ->build();

    newMachine->getIcon()->setPos(this->pos);

    auto [newId, newName] = schema->ids->getNewMachineBase();
    newMachine->conf->setId(newId);
    newMachine->conf->setName(newName);

    qDebug() << "Returning a cloned machine...";
    return newMachine;
}

std::vector<LinkCloner *> MachineCloner::getConnectedLinkCloners()
{
    return this->linkCloners;
}
void MachineCloner::addConnectedLink(LinkCloner *linkCloner)
{
    this->linkCloners.push_back(linkCloner);
}
