#include "components/connectable.h"
#include <memory>

class ConnectableSet : public Connectable
{
public:
    std::vector<std::shared_ptr<Link>> *getConnectedLinks() override;
    void                                setConnectedLinks(
                                       std::vector<std::shared_ptr<Link>> *linksVector) override;
    void        removeConnectedLink(Link *link) override;
    void        addConnectedLink(std::shared_ptr<Link> link) override;
    PixmapIcon *getIcon() override;
    unsigned    getId() const override;
    void        setId(unsigned newId) override;
    std::unique_ptr<std::vector<std::string>> print() override;
    std::unique_ptr<ConnectableCloner> cloner(SchemaCloner *parent) override;

private:
    std::unique_ptr<ConnectableSetConfiguration> conf;
    std::unique_ptr<PixmapIcon>                  icon;
};
