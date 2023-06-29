#include <QDebug>
#include "qboxlayout.h"
#include "window/cluster.h"
#include "drawingtable/scene.h"
#include "qwidget.h"

ClusterWindow::ClusterWindow(QWidget *parent) : QMainWindow{parent}
{
    view  = new View(this);
    scene = new Scene(this);
    view->setGScene(scene);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(view);

    auto *mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget(mainWidget);

    qDebug() << this->rect();
    this->show();
}
