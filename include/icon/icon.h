#ifndef ICON_H
#define ICON_H

#include "components/connection.h"
#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"
#include "window/machineconfiguration.h"
#include "window/users.h"
#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <map>
#include <memory>
#include <string>

class Link;
class Connection;
class Item;

// Define a estrutura para armazenar as configurações do ícone
struct IconConfiguration
{
    QString CompPower_lineEdit;
    QString cores_lineEdit;
    QString energyconsumer_lineEdit;
    QString labelEdit;
    QString lineEdit_4;
    QString loadFactor_lineEdit;
    QString primarystorage_lineEdit;
    QString secondaryStorage_lineEdit;

    int  ownercomboBoxIndex;
    int  schedulingcomboBoxIndex;
    bool checkBoxState;
    // Adicione mais campos aqui, se necessário
    IconConfiguration()
        : ownercomboBoxIndex(0), schedulingcomboBoxIndex(0),
          checkBoxState(false)
    {
        // Define os valores iniciais dos campos conforme necessário
        labelEdit = ""; // Por exemplo, defina uma string vazia como valor
                        // inicial para textValue
        CompPower_lineEdit        = "";
        cores_lineEdit            = "";
        energyconsumer_lineEdit   = "";
        lineEdit_4                = "";
        loadFactor_lineEdit       = "";
        primarystorage_lineEdit   = "";
        secondaryStorage_lineEdit = "";
    }
};

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char    *name,
         Connection    *owner  = nullptr,
         QGraphicsItem *parent = nullptr);
    Icon(Icon& icon);
    virtual ~Icon(){};

    bool                        isSelected;
    unsigned                    id;
    bool                        select;

    std::string iconPath;
    std::string iconPathSelected;

    // Funções para salvar e carregar as configurações do ícone
    void                        saveConfiguration();
    void                        loadConfiguration();
    Connection                 *getOwner();
    void                        selection(bool select);
    void                        deselect();
    void                        setOutputLabel(QLabel *label);
    std::string                *getName();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void                         updatePosition();
    QString                      positionString;
    QLabel                      *outputLabel;
    std::unique_ptr<std::string> name;
    IconConfiguration configuration; // Adicione o membro de dados para
                                     // armazenar a configuração
    Connection *owner;

signals:
};

#endif
