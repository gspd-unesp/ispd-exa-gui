#ifndef ICON_H
#define ICON_H

#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"
#include <QGraphicsItem>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <map>
#include <string>
#include <QDialog>
#include "window/machineconfiguration.h"
#include <QGraphicsView>
#include "window/users.h"


class Link;
class Item;

// Define a estrutura para armazenar as configurações do ícone
struct IconConfiguration {
    QString CompPower_lineEdit;
    QString cores_lineEdit;
    QString energyconsumer_lineEdit;
    QString labelEdit;
    QString lineEdit_4;
    QString loadFactor_lineEdit;
    QString primarystorage_lineEdit;
    QString secondaryStorage_lineEdit;

    int ownercomboBoxIndex;
    int schedulingcomboBoxIndex;
    bool checkBoxState;
    // Adicione mais campos aqui, se necessário
    IconConfiguration() : ownercomboBoxIndex(0), schedulingcomboBoxIndex(0), checkBoxState(false) {
        // Define os valores iniciais dos campos conforme necessário
        labelEdit = ""; // Por exemplo, defina uma string vazia como valor inicial para textValue
        CompPower_lineEdit = "";
        cores_lineEdit = "";
        energyconsumer_lineEdit = "";
        lineEdit_4 = "";
        loadFactor_lineEdit = "";
        primarystorage_lineEdit = "";
        secondaryStorage_lineEdit = "";
    }
};

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    ~Icon();

    bool                        isSelected;
    unsigned                    id;
    std::map<unsigned, Link *> *links;
    bool             select;

    std::string iconPath;
    std::string iconPathSelected;



    // Funções para salvar e carregar as configurações do ícone
    void saveConfiguration();
    void loadConfiguration();
    void selection(bool select);
    void deselect();
    /* void                        deselect(); */
    void                        setLinks(std::map<unsigned, Link *> *links);
    std::map<unsigned, Link *> *getLinks();
    void                        setOutputLabel(QLabel *label);
    std::string                *getName();

    void setItem(Item *item);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void         updatePosition();
    QString      positionString;
    QLabel      *outputLabel;
    std::string *name;
    IconConfiguration configuration; // Adicione o membro de dados para armazenar a configuração
    Item                       *item;

signals:
};

#endif
