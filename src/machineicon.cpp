#include "src/machineicon.h"
#include "qgraphicsitem.h"

MachineIcon::MachineIcon(const char *name, QGraphicsItem *parent)
    : Icon{name, parent}
{
    auto pixmap = QPixmap::fromImage(QImage(this->iconPath)).scaled(QSize(50, 50));

    this->setPixmap(pixmap);
}
