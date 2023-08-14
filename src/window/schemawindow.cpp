#include "window/schemawindow.h"
#include "window/drawingtable/drawingtable.h"
#include <QDebug>
#include <QWidget>

SchemaWindow::SchemaWindow(Schema *schema, QWidget *parent)
    : QMainWindow{parent}
{
    this->schema = schema;
    drawingTable = new DrawingTable(schema, this);

    this->setCentralWidget(drawingTable);

    qDebug() << this->rect();
}
