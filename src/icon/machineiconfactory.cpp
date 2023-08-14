#include "icon/machineiconfactory.h"
#include "components/machine.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/pixmappair.h"
#include "utils/iconPath.h"

PixmapIcon *MachineIconFactory::iconBuilder(Machine *machine)
{
    PixmapIconBuilder iconBuilder;
    return iconBuilder.setOwner(machine)
        ->setPixmapPair(PixmapPair(machinePath, machinePathSelected))
        ->build();
}
