#pragma once

#include <string>

class LinkConfiguration
{
public:
    explicit LinkConfiguration(std::string_view const name);

    std::string getName() const;
    void        setName(std::string_view const newName);
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
