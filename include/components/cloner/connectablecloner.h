#pragma once

#include "components/cloner/cloner.h"
#include "components/connection.h"
#include "icon/pixmapicon.h"

class ConnectableCloner : public Cloner
{
public:
    virtual Connectable *clone(Schema *schema) = 0;
};
