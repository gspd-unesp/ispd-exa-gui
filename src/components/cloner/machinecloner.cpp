#include "components/cloner/machinecloner.h"
#include "components/conf/machineconfiguration.h"
#include "components/machinebuilder.h"
#include "components/schema.h"
#include "icon/pixmapicon.h"
#include <memory>
#include <string>

MachineCloner::MachineCloner(Machine *base, SchemaCloner *parent)
{
    qDebug() << "Before copying machine conf.";
    this->clonedConf = new MachineConfiguration(*base->conf);
    this->parent     = parent;
    qDebug() << "Before getting machineIcon scenePos.";
    this->pos = base->getIcon()->scenePos();
}

std::unique_ptr<Machine> MachineCloner::clone(Schema *schema)
{
    MachineConfiguration *newMachineConfiguration =
        new MachineConfiguration(*this->clonedConf);
    Machine *newMachine = MachineBuilder()
                              .setSchema(schema)
                              ->setConf(newMachineConfiguration)
                              ->build();

    newMachine->getIcon()->setPos(this->pos);
    newMachine->conf->setId(schema->schemaIds->machineId++);
    newMachine->conf->setName("Machine" +
                              std::to_string(newMachine->conf->getId()));

    return std::unique_ptr<Machine>(newMachine);
}
