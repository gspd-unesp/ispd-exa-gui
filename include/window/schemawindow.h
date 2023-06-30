#pragma once

#include <QMainWindow>

class Schema;
class DrawingTable;

class SchemaWindow : public QMainWindow
{
    Q_OBJECT

public:
    Schema *schema;
    SchemaWindow(Schema *schema, QWidget *parent = nullptr);

private:
    DrawingTable *drawingTable;
};
