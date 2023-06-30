#pragma once
#include "item/machineicon.h"
#include "qradiobutton.h"
#include "view.h"
#include <QWidget>

class Schema;
class SchemaIcon;

class DrawingTable : public QWidget
{
    Q_OBJECT
private:
    Scene *scene;
    View  *view;

    QWidget *buttonsRow;
    QHBoxLayout *buttonsLayout;
    QRadioButton *pcButton;
    QRadioButton *schemaButton;
    QRadioButton *linkButton;
    QRadioButton *noneButton;
    void setupPcButton();
    void setupNoneButton();
    void setupSchemaButton();
    void setupLinkButton();

public:
    DrawingTable(QFrame *parent = nullptr);
    DrawingTable(Schema *schema, QWidget *parent = nullptr);
    Schema *schema;


    void         pcButtonClicked();
    void         schemaButtonClicked();
    void         linkButtonClicked();
    void         noneButtonClicked();

    MachineIcon *addMachine();
    SchemaIcon  *addSchema();
    Link        *addLink();
};
