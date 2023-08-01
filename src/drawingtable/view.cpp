#include "drawingtable/view.h"
#include "drawingtable/scene.h"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include "item/icon.h"

/*
 * Create the item following the QGraphicsView constructor
 */
View::View(QWidget *parent) : QGraphicsView{parent}
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform);
}

void View::setGScene(Scene *scene)
{
    this->setScene(scene);
    this->gScene = scene;
}

/*
 * Configure the event of clicking the View to print the location
 * of the mouse at the moment.
 */
void View::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos().x();
    qDebug() << event->pos().y();

    if (event->button() == Qt::RightButton) {
        qDebug() << "Custom view clicked with right.";
    }

    if (event->button() == Qt::LeftButton) {
        qDebug() << "Custom view clicked with left.";
    }

           // Deselect all icons if the clicked area has no icons
    QGraphicsItem* clickedItem = itemAt(event->pos().x(), event->pos().y());
    if (!clickedItem) {
        qDebug() << "Clicou em uma área vazia (retirar a seleção)";
        for (auto item : this->items()) {
            if (Icon* icon = dynamic_cast<Icon*>(item)) {
                icon->deselect();
            }
        }
    }

    if (event->button() == Qt::LeftButton) {
        this->startSelection = event->pos();
        this->selectionRect = new QGraphicsRectItem();
        this->selectionRect->setPen(QPen(Qt::red, 2, Qt::DashLine)); // Change color and pen style
        this->selectionRect->setBrush(QBrush(QColor(100, 100, 255)));
        // this->selectionRect->setRect(QRectF(this->startSelection, event->pos()).normalized());


               // Definir um tamanho maior para o retângulo (por exemplo, 100x100)
        QRectF rect(QPointF(0, 0), QSizeF(100, 100));
        rect.moveCenter(this->startSelection);
        this->selectionRect->setRect(rect);


               // Print the bounding rectangle of the selectionRect and the scene
        qDebug() << "Selection Rect Bounding Rect: " << this->selectionRect->boundingRect();
        qDebug() << "Scene Bounding Rect: " << this->sceneRect();

        qDebug() << "Número de Itens na Cena antes:" << this->gScene->items().count();

                                                        this->gScene->addItem(this->selectionRect); // Add the selection rectangle to the scene
        qDebug() << "area de selecao adicionada na cena";
        qDebug() << "Número de Itens na Cena agora:" << this->gScene->items().count();
    }

    QGraphicsView::mousePressEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if (this->startSelection != QPoint()) {
        // Update the selection rectangle while dragging the mouse
        QRectF selectionAreaRect = QRectF(this->startSelection, event->pos()).normalized();
        this->selectionRect->setRect(selectionAreaRect);
        //qDebug() << "arrastando o mouse";
    }

    QGraphicsView::mouseMoveEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->startSelection != QPoint()) {
        // Calculate the selection area rectangle
        QRectF selectionAreaRect = QRectF(this->startSelection, event->pos()).normalized();

               // Deselect all icons outside the selection area
        for (auto item : this->items()) {
            if (Icon *icon = dynamic_cast<Icon *>(item)) {
                if (selectionAreaRect.contains(icon->sceneBoundingRect())) {
                    icon->select();
                } else {
                    icon->deselect();
                }
            }
        }

               // Reset the initial position for area selection
        this->startSelection = QPoint();
        this->gScene->removeItem(this->selectionRect); // Remove the selection rectangle from the scene
        delete this->selectionRect;
        this->selectionRect = nullptr;
    }

    QGraphicsView::mouseReleaseEvent(event);
}
