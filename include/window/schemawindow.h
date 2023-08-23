#pragma once

#include <QMainWindow>

class Schema;
class DrawingTable;

class SchemaWindow : public QMainWindow
{
    Q_OBJECT

public:
    Schema *schema;
    explicit SchemaWindow(Schema *schema, QWidget *parent = nullptr);
    DrawingTable *drawingTable;
};
