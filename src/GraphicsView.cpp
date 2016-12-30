#include "GraphicsView.hpp"
#include "moc_GraphicsView.cpp"
#include "GraphicsScene.hpp"
#include "GraphicsGate.hpp"
#include <cmath>
#include <QResizeEvent>


GraphicsView::GraphicsView(GraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
    setAlignment(Qt::AlignCenter);
    connect(scene, &GraphicsScene::newGate, [this, scene](GraphicsGate*) {
            QRectF bounds = scene->itemsBoundingRect();
            QSizeF size(std::max(-bounds.left(), bounds.right()),
                        std::max(-bounds.top(), bounds.bottom()));
            this->fixSceneRect(size*2);
        });
    setSceneRect(frameRect() + QMarginsF(100, 100, 100, 100));
}

void GraphicsView::fixSceneRect(const QSizeF& size) {
    QMarginsF margin(padding, padding, padding, padding);
    QSizeF oldSize = sceneRect().size();

    oldSize.setWidth(oldSize.width()-2*padding);
    oldSize.setHeight(oldSize.width()-2*padding);
    QSize newSize(std::max(oldSize.width(), size.width()),
                  std::max(oldSize.height(), size.height()));
    QPointF pos(-newSize.width()/2, -newSize.height()/2);
    setSceneRect(QRectF(pos, newSize) + margin);
}

void GraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    QSizeF oldSize = sceneRect().size();
    QSizeF size = event->size();

    QMarginsF margin(padding, padding, padding, padding);

    if (!oldSize.isValid()) {
        QPointF pos(-size.width()/2, -size.height()/2);
        setSceneRect(QRectF(pos, size) + margin);
        centerOn(sceneRect().center());
    } else {
        fixSceneRect(size);
    }

    fixSceneRect(event->size());
}
