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

    /* Schema mainSchema; */
    /*  */
    /* unsigned otherSchemaId = mainSchema.allocateNewSchema(); */
    /*     unsigned a = mainSchema.allocateNewMachine(); */
    /*     unsigned b = mainSchema.allocateNewMachine(); */
    /*     mainSchema.allocateNewLink(LinkConnections{ */
    /*         .begin = mainSchema.connectables[a].get(), .end = mainSchema.connectables[b].get()}); */
    /*  */
    /* auto *schema = */
    /*     static_cast<Schema *>(mainSchema.connectables[otherSchemaId].get()); */
    /* for (int i = 0; i < 50; i++) { */
    /*     unsigned newSchemaId = schema->allocateNewSchema(); */
    /*     schema->allocateNewMachine(); */
    /*     schema->allocateNewSwitch(); */
    /*     unsigned c = schema->allocateNewMachine(); */
    /*     unsigned d = schema->allocateNewMachine(); */
    /*     schema->allocateNewMachine(); */
    /*  */
    /*     schema->allocateNewLink(LinkConnections{ */
    /*         .begin = schema->connectables[c].get(), .end = schema->connectables[d].get()}); */
    /*     schema = static_cast<Schema *>(schema->connectables[newSchemaId].get()); */
    /* } */
    /*  */
    /* mainSchema.print_as_root(); */
    /*  */
    /* SchemaCloner mainCloner(&mainSchema); */
    /* auto clonedSchema = mainCloner.clone(&mainSchema); */
    /* static_cast<Schema *>(clonedSchema.get())->print_as_root(); */
    /* clonedSchema->print_as_root(); */
    MainWindow mw;
    mw.setWindowTitle("iSPD");
    mw.show();

    return app.exec();
}
