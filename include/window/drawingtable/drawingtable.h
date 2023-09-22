#pragma once
#include "window/drawingtable/view.h"
#include "window/simulation.h"
#include "window/users.h"
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

    /* QList<QString> list1Data; */
    /* QList<double>  list2Data; */

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

    void setupPcButton();
    void setupSwitchButton();
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
    void   pcButtonClicked();
    void   schemaButtonClicked();
    void   linkButtonClicked();
    void   noneButtonClicked();
    void   openUserWindowClicked();
    void   openSimulationWindowClicked();
    void   addIcons(std::vector<Connectable *> *items);
    Scene *getScene();

    void receiveUserWindowData(const QList<QString> &list1Data,
                               const QList<double>  &list2Data);

    PixmapIcon *addSwitch();
    PixmapIcon *addMachine();
    PixmapIcon *addSchema();
    Link       *addLink(LinkConnections connections);
};
