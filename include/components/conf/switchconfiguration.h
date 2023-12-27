#pragma once
#include "components/conf/itemconfiguration.h"

class SwitchConfiguration : public ItemConfiguration
{
public:
    explicit SwitchConfiguration(std::string_view const &name);

    std::string getName() const override;
    void        setName(std::string_view const &newName) override;
    unsigned    getBandwidth() const;
    void        setBandwidth(const unsigned newBandwidth);
    double      getLatency() const;
    void        setLatency(const double newLatency);
    double      getloadFactor() const;
    void        setloadFactor(const double newloadFactor);

private:
    std::string name;
    unsigned    bandwidth;
    double      loadFactor;
    double      latency;
};

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void to_json(json &j, const SwitchConfiguration &sc);
