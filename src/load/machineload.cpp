#include "load/machineload.h"
#include "load/linkload.h"
#include <vector>

MachineLoad::MachineLoad(Schema *schema, unsigned id)
{
    this->schema   = schema;
    this->id       = id;
    this->linksIds = new std::vector<unsigned>;
}

MachineLoad::~MachineLoad()
{
    for (auto linkId = this->linksIds->begin(); linkId != this->linksIds->end();
         linkId++) {
        LinkLoad *deletableLink = this->schema->links->at(*linkId);

        delete (deletableLink);

        this->schema->links->erase(*linkId);
    }

    delete this->linksIds;
}
