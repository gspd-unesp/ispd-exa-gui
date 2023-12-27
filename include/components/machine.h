#pragma once

#include <memory>
#include <string>
#include <vector>

#include "components/connectable.h"
#include "nlohmann/json.hpp"
#include "window/machineconfigurationwindow.h"

class Schema;
class SchemaCloner;
class Link;
class Icon;
class Cloner;
class ItemConfiguration;
class MachineConfiguration;

class Machine : public Connectable
{
public:
    Machine(Schema *schema, MachineConfiguration *conf);
    ~Machine();

    std::vector<std::shared_ptr<Link>> *getConnectedLinks() override;

    void setConnectedLinks(std::vector<std::shared_ptr<Link>> *map) override;
    void removeConnectedLink(Link *link) override;
    void addConnectedLink(std::shared_ptr<Link> link) override;
    std::unique_ptr<std::vector<std::string>> print() override;

    void                               showConfiguration() override;
    PixmapIcon                        *getIcon() override;
    ItemConfiguration                 *getConf() override;
    std::unique_ptr<ConnectableCloner> cloner(
        SchemaCloner *parent = nullptr) override;

    std::vector<std::shared_ptr<Link>> connectedLinks;

    Schema *schema;

    std::unique_ptr<MachineConfiguration> conf;
    std::unique_ptr<PixmapIcon>           icon;
    unsigned                              getId() const override;
    void                                  setId(unsigned newId) override;
        /* j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}}; */

        /* j.at("name").get_to(p.name); */
        /* j.at("address").get_to(p.address); */
        /* j.at("age").get_to(p.age); */

private:
    unsigned                                    id;
    std::unique_ptr<MachineConfigurationWindow> window;
};


using json = nlohmann::json;

void to_json(json& j, const Machine& m);
void from_json(const json& j, Machine& m);
