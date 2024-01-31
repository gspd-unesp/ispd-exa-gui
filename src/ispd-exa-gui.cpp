#include "context/context.h"
#include <memory>
#include <window/simulation.h>
#include <window/main.h>
#include <QApplication>
#include <QScreen>
#include "components/schema.h"
#include "components/conf/machineconfiguration.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mw;
    mw.setWindowTitle("iSPD");
    mw.show();

    return app.exec();
}
