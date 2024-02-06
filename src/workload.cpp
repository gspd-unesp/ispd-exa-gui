// workload.cpp
#include "context/workload.h"

namespace Context {
void to_json(nlohmann::json& j, const Workload& m) {
    j = {
         {"type", m.getTypeString()},
         {"owner", m.owner},
         {"remaining_tasks", m.remainingTasks},
         {"master_id", m.master_id},
         {"computing_offload", m.computingOffload},
         {
             "interarrival_type", {
                 {"type", m.arrivalType->getTypeString()},
                 {"lambda", m.arrivalType->lambda},
                 {"shape", m.arrivalType->shape}
             }
         },
         {"min_proc_size", m.minProcSize},
         {"max_proc_size", m.maxProcSize},
         {"min_comm_size", m.minCommSize},
         {"max_comm_size", m.maxCommSize},
         };

}
}
