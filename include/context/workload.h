#pragma once

#include "components/machine.h"
#include "context/user.h"
#include <memory>
#include <qdebug.h>

namespace Context
{
enum WORKLOAD_TYPE
{
    UNIFORM,
};

enum INTERARRIVAL_TYPE
{
    POISSON,
};

struct Workload
{
    struct InterarrivalType
    {
        INTERARRIVAL_TYPE type   = POISSON;
        double            lambda = 0.0;

        QString getTypeString()
        {
            switch (this->type) {
            case POISSON:
                return "poisson";
            default:
                qDebug() << "Interarrival type is unknown or unimplemented\n";
                return "";
            }
        }
    };

    WORKLOAD_TYPE            type = UNIFORM;
    std::shared_ptr<User>    owner;
    Machine *master = nullptr;
    unsigned                 remainingTasks   = 0;
    double                   computingOffload = 0.0;
    InterarrivalType         arrivalType;
    double                   minProcSize = 0.0;
    double                   maxProcSize = 0.0;
    double                   minCommSize = 0.0;
    double                   maxCommSize = 0.0;

    QString getTypeString()
    {
        switch (this->type) {
        case UNIFORM: {
            return "uniform";
        }
        default: {
            qDebug() << "Workload type is unknown or unimplemented\n";
            return "";
        }
        }
    }
};

} // namespace Context
