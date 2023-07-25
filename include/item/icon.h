#ifndef ICON_H
#define ICON_H

#include "qgraphicsscene.h"
#include <QGraphicsItem>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <map>
#include <string>
#include <QDialog>
#include "window/machineconfiguration.h"

class Link;

// Define a estrutura para armazenar as configurações do ícone
struct IconConfiguration {
    QString textValue;
    int comboBoxIndex;
    bool checkBoxState;
    // Adicione mais campos aqui, se necessário
    IconConfiguration() : comboBoxIndex(0), checkBoxState(false) {
        // Define os valores iniciais dos campos conforme necessário
        textValue = ""; // Por exemplo, defina uma string vazia como valor inicial para textValue
    }
};

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    ~Icon();
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void             setOutputLabel(QLabel *label);
    std::map<unsigned, Link *> *links;
    std::string     *getName();
    bool             isSelected;
    unsigned         id;

    std::string iconPath;
    std::string iconPathSelected;

    void deselect();

    // Funções para salvar e carregar as configurações do ícone
    void saveConfiguration();
    void loadConfiguration();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void         updatePosition();
    void         select();
    QString      positionString;
    QLabel      *outputLabel;
    std::string *name;
    IconConfiguration configuration; // Adicione o membro de dados para armazenar a configuração
signals:
};

#endif
