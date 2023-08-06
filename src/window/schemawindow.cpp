#include <QDebug>
#include "qdebug.h"
#include "window/schemawindow.h"
#include "qwidget.h"
#include "window/drawingtable/drawingtable.h"

SchemaWindow::SchemaWindow(Schema *schema, QWidget *parent) : QMainWindow{parent}
{
    this->schema = schema;
    drawingTable = new DrawingTable(schema, this);

    this->setCentralWidget(drawingTable);

    qDebug() << this->rect();
}
