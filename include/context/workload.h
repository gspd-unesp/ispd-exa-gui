// workload.h
#ifndef WORKLOAD_H
#define WORKLOAD_H
#include "components/machine.h"
#include "context/user.h"
#include <string>
#include <memory>
#include <qdebug.h>
#include <nlohmann/json.hpp>

namespace Context
{
enum WORKLOAD_TYPE
{
    UNIFORM,
    CONSTANT,
    TWO_STAGE_UNIFORM
};

enum INTERARRIVAL_TYPE
{
    FIXED,
    POISSON,
    EXPONENTIAL,
    WEIBULL
};

typedef struct Workload
{
    typedef struct InterarrivalType
    {
        INTERARRIVAL_TYPE type   = POISSON;
        double            lambda = 0.0;
        double            shape = 0.0;

        std::string getTypeString() const
        {
            switch (this->type) {
            case POISSON:
                return "poisson";
            case FIXED:
                return "fixed";
            case EXPONENTIAL:
                return "exponential";
            case WEIBULL:
                return "weibull";
            default:
                qDebug() << "Interarrival type is unknown or unimplemented\n";
                return "";
            }
        }
    }InterarrivalType;

    WORKLOAD_TYPE            type = UNIFORM;
    std::string               owner;
    unsigned                 master_id;
    unsigned                 remainingTasks   = 0;
    double                   computingOffload = 0.0;
    InterarrivalType         *arrivalType;
    double                   minProcSize = 0.0;
    double                   maxProcSize = 0.0;
    double                   minCommSize = 0.0;
    double                   maxCommSize = 0.0;

    std::string getTypeString () const
    {
        switch (this->type) {
        case UNIFORM:
            return "uniform";
        case CONSTANT:
            return "constant";
        case TWO_STAGE_UNIFORM:
            return "two stage uniform";
        default:
            qDebug() << "Workload type is unknown or unimplemented\n";
            return "";
        }
    }


} Workload;


void to_json( nlohmann::json& j, const Workload& m);
} // namespace Context




#endif // WORKLOAD_H


