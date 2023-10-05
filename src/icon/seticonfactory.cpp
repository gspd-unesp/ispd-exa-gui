#include "icon/pixmapicon.h"
#include "components/connectableset.h"
#include "icon/pixmapiconbuilder.h"
#include "icon/seticonfactory.h"
#include "utils/iconPath.h"

PixmapIcon *SetIconFactory::iconBuilder(ConnectableSet *set)
{
    PixmapIconBuilder iconBuilder;
    return iconBuilder.setOwner(set)
        ->setPixmapPair(PixmapPair(setPath, setPathSelected))
        ->build();
}
