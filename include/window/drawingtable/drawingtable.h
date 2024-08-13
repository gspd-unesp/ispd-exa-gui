#pragma once
#include "context/context.h"
#include "icon/pixmapicon.h"
#include "window/drawingtable/view.h"
#include "window/simulation.h"
#include "window/users.h"
#include "window/schedulergenerator.h"
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

struct LinkConnections;
class Schema;
class Link;

class DrawingTable : public QWidget
{
    Q_OBJECT
private:
    Scene *scene;
    View  *view;

    QWidget      *buttonsRow;
    QHBoxLayout  *buttonsLayout;
    QRadioButton *pcButton;
    QRadioButton *setButton;
    QRadioButton *schemaButton;
    QRadioButton *linkButton;
    QRadioButton *noneButton;

    QPushButton *openUserWindow;
    QPushButton *openSimulationWindow;
    QPushButton *openSchedulerGenerator;
    Context::MainContext mainContext;

    UserWindow *userWindow;
    Simulation *simulationWindow;

    void setupPcButton();
    void setupSwitchButton();
    void setupSetButton();
    void setupNoneButton();
    void setupSchemaButton();
    void setupLinkButton();

    QGraphicsRectItem *selectionRectItem =
        nullptr; // Novo membro para o retângulo de seleção
    void addSelectionRectToScene(const QRectF &rect);
    void removeSelectionRectFromScene();

public:
    DrawingTable(QFrame *parent = nullptr);
    DrawingTable(Schema *schema, QWidget *parent = nullptr);
    Schema *schema;

    void   switchButtonClicked();
    void   setButtonClicked();
    void   pcButtonClicked();
    void   schemaButtonClicked();
    void   linkButtonClicked();
    void   noneButtonClicked();
    void   openUserWindowClicked();
    void   openSimulationWindowClicked();
    void openWorkloadWindow();
    void openSchedulerGeneratorClicked();
    void   addIcons(std::vector<Connectable *> *items);
    Scene *getScene();

    void receiveUserWindowData(const QList<QString> &list1Data,
                               const QList<double>  &list2Data);

    PixmapIcon *addSwitch();
    PixmapIcon *addMachine();
    PixmapIcon *addSchema();
    PixmapIcon *addSet();
    Link       *addLink(LinkConnections connections);
};
