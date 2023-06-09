#include "window/settings.h"
#include <ui_settingswindow.h>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
