#pragma once 

#include <string>
#include <nlohmann/json.hpp>

namespace Context {
    typedef struct {
        std::string name;
        double allowedUsage;
    } User;

    inline void to_json(nlohmann::json &j, const User &u) {
        j["name"] = u.name;
        j["energy_consumption_limit"] = u.allowedUsage;
    }
}
