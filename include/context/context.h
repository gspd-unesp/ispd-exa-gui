#pragma once

#include <memory>
#include <vector>
#include "user.h"
#include "workload.h"

class Schema;
namespace Context {
    struct MainContext {
        std::vector<User> users;
        std::vector<Workload> workloads;
        std::shared_ptr<Schema> mainSchema;
    };
}
