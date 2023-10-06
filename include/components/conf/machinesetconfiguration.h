#include "components/conf/itemconfiguration.h"

class MachineSetConfiguration : public ItemConfiguration
{
public:
    explicit MachineSetConfiguration(std::string_view const &name);
    std::string getName() const override;
    void        setName(std::string_view const &name) override;
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
