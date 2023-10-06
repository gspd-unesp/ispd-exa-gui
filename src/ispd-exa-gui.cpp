#include "components/cloner/schemacloner.h"
#include "components/connectable.h"
#include "components/schema.h"
#include "window/main.h"
#include <iostream>
#include <window/simulation.h>

#include <QApplication>
#include <QScreen>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mw;
    mw.setWindowTitle("iSPD");
    mw.show();

    return app.exec();
}
