#include "context/context.h"
#include <memory>
#include <window/simulation.h>
#include "window/addworkloadwindow.h"

#include <QApplication>
#include <QScreen>
#include "components/schema.h"
#include "components/conf/machineconfiguration.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Context::MainContext mainContext;
    mainContext.mainSchema = std::make_shared<Schema>();
    auto i = mainContext.mainSchema.get()->allocateNewMachine();
    auto j = mainContext.mainSchema.get()->allocateNewMachine();

    auto machineI = static_cast<Machine *>(mainContext.mainSchema->connectables[i].get());
    static_cast<MachineConfiguration *>(machineI->getConf())->master = true;

    auto machineJ = static_cast<Machine *>(mainContext.mainSchema->connectables[j].get());
    static_cast<MachineConfiguration *>(machineJ->getConf())->master = true;

    AddWorkloadWindow mw(&mainContext, nullptr);
    /* MainWindow mw; */
    /* mw.setWindowTitle("iSPD"); */
    mw.show();

    return app.exec();
}
