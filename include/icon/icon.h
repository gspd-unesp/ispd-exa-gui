#ifndef ICON_H
#define ICON_H

/* #include "qgraphicsscene.h" */
/* #include "qgraphicssceneevent.h" */
/* #include "window/machineconfiguration.h" */
/* #include "window/users.h" */
/* #include <QDialog> */
/* #include <QGraphicsItem> */
/* #include <QGraphicsView> */
/* #include <QLabel> */
/* #include <QObject> */
/* #include <QVector> */
/* #include <map> */
/* #include <memory> */
/* #include <string> */

class Link;

struct Conf
{
    /* QPointF pos; */
};

// Define a estrutura para armazenar as configurações do ícone
/* struct IconConfiguration */
/* { */
/*     QString CompPower_lineEdit; */
/*     QString cores_lineEdit; */
/*     QString energyconsumer_lineEdit; */
/*     QString labelEdit; */
/*     QString lineEdit_4; */
/*     QString loadFactor_lineEdit; */
/*     QString primarystorage_lineEdit; */
/*     QString secondaryStorage_lineEdit; */
/*  */
/*     int  ownercomboBoxIndex; */
/*     int  schedulingcomboBoxIndex; */
/*     bool checkBoxState; */
/*     // Adicione mais campos aqui, se necessário */
/*     IconConfiguration() */
/*         : ownercomboBoxIndex(0), schedulingcomboBoxIndex(0), */
/*           checkBoxState(false) */
/*     { */
/*         // Define os valores iniciais dos campos conforme necessário */
/*         labelEdit = ""; // Por exemplo, defina uma string vazia como valor */
/*                         // inicial para textValue */
/*         CompPower_lineEdit        = ""; */
/*         cores_lineEdit            = ""; */
/*         energyconsumer_lineEdit   = ""; */
/*         lineEdit_4                = ""; */
/*         loadFactor_lineEdit       = ""; */
/*         primarystorage_lineEdit   = ""; */
/*         secondaryStorage_lineEdit = ""; */
/*     } */
/* }; */

template <class OwnerT>
class Icon
{
public:
    virtual OwnerT *getOwner() = 0;
    virtual void  toggleSelect() = 0;
    /*     Q_OBJECT */
    /* public: */
    /*     explicit Icon(Connection *owner = nullptr, QGraphicsItem *parent =
     * nullptr); */
    /*     Icon(Icon &icon); */
    /*     virtual ~Icon(){}; */
    /*  */
    /*     unsigned id; */
    /*     bool     select; */
    /*  */
    /*     std::string iconPath; */
    /*     std::string iconPathSelected; */
    /*  */
    /*     // Funções para salvar e carregar as configurações do ícone */
    /*     void         saveConfiguration(); */
    /*     void         loadConfiguration(); */
    /*  */
    /* protected: */
    /*     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override; */
    /*     void mousePressEvent(QGraphicsSceneMouseEvent *event) override; */
    /*     void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; */
    /*  */
    /* private: */
    /*     void                         updatePosition(); */
    /*     QString                      positionString; */
    /*     QLabel                      *outputLabel; */
    /*     IconConfiguration configuration; // Adicione o membro de dados para
     */
    /*     // armazenar a configuração */
    /*     Connection *owner; */
    /*  */
    /* signals: */
};

#endif
