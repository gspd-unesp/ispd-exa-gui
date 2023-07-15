#pragma once
#include "drawingtable/view.h"
#include "item/machineicon.h"
#include "window/users.h"
#include "window/simulation.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QWidget>

class Schema;
class SchemaIcon;

class DrawingTable : public QWidget
{
    Q_OBJECT
private:
    Scene *scene;
    View  *view;

    QWidget      *buttonsRow;
    QHBoxLayout  *buttonsLayout;
    QRadioButton *pcButton;
    QRadioButton *schemaButton;
    QRadioButton *linkButton;
    QRadioButton *noneButton;

    QPushButton *openUserWindow;
    QPushButton *openSimulationWindow;

    UserWindow *userWindow;
    Simulation *simulationWindow;

    void          setupPcButton();
    void          setupNoneButton();
    void          setupSchemaButton();
    void          setupLinkButton();

public:
    DrawingTable(QFrame *parent = nullptr);
    DrawingTable(Schema *schema, QWidget *parent = nullptr);
    Schema *schema;

    void pcButtonClicked();
    void schemaButtonClicked();
    void linkButtonClicked();
    void noneButtonClicked();
    void openUserWindowClicked();
    void openSimulationWindowClicked();

    MachineIcon *addMachine();
    SchemaIcon  *addSchema();
    Link        *addLink();
};
