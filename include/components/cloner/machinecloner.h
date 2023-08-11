class SchemaCloner;
class Machine;

class MachineCloner
{
public:
    MachineCloner(Machine *base, SchemaCloner *parent);
private:
    Machine *base;
};
