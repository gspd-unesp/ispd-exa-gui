#include "components/machinebuilder.h"
#include "icon/pixmapicon.h"
#include "components/machine.h"
#include "components/schema.h"
#include "components/conf/machineconfiguration.h"

MachineBuilder::MachineBuilder() {}

MachineBuilder *MachineBuilder::setSchema(Schema *schema) {
    this->schema = schema;
    return this;
}
MachineBuilder *MachineBuilder::setIcon(PixmapIcon *icon) {
    this->icon = icon;
    return this;
}
MachineBuilder *MachineBuilder::setConf(MachineConfiguration *conf) {
    this->conf = conf;
    return this;
}

Machine *MachineBuilder::build() {
    return new Machine(this->schema, this->conf);
}
