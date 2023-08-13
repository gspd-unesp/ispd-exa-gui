#include "components/item.h"
#include "qpixmap.h"

class PixmapIcon;
class Connection;

class PixmapIconBuilder
{
public:
    PixmapIconBuilder();

    PixmapIconBuilder *setOwner(Connection *item);
    PixmapIconBuilder *setPixmap(QPixmap pixmap);

    PixmapIcon *build();

private:
    Connection *owner;
    QPixmap pixmap;
};
