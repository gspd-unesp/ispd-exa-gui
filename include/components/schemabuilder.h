class Schema;
class SchemaConfiguration;
class PixmapIcon;

class SchemaBuilder
{
public:
    SchemaBuilder();
    SchemaBuilder *setSchema(Schema *schema);
    SchemaBuilder *setConf(SchemaConfiguration *conf);
    Schema        *build();

private:
    Schema              *schema;
    PixmapIcon          *icon;
    SchemaConfiguration *conf;
};
