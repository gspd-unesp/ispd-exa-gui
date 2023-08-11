#include <memory>
class SchemaCloner;
class Machine;

class MachineCloner
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent);
    std::unique_ptr<Machine> clone();

private:
    Machine *base;
};
