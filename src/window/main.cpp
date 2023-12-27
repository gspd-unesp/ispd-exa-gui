#include "window/main.h"
#include <QBrush>
#include <QColor>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPen>
#include <QPixmap>
#include <QPushButton>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show() {
    if (this->context != nullptr) {
        qDebug() << "Need a context!";
        return;
    }

    QMainWindow::show();
}
