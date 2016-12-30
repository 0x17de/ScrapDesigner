#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include "GraphicsScene.hpp"
#include "moc_GraphicsScene.cpp"
#include "GraphicsGate.hpp"


GraphicsScene::GraphicsScene(QObject* parent, GateHandleMap& gateHandles)
    : QGraphicsScene(parent)
    , gateHandles_{gateHandles}
{
    setSceneRect(QRectF(0, 0, 10, 10));
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted() && gateHandles_.contains(selectedGateTool_)) {
        GraphicsGate* gate = gateHandles_[selectedGateTool_].spawn(activePanel(), event->lastScenePos());
        connect(gate, &GraphicsGate::selected, [this, gate]{
                QRectF rect = gate->boundingRect();
                rect.moveTo(gate->pos());
                if (!selection_) {
                    selection_ = this->addRect(rect);
                } else {
                    selection_->setRect(rect);
                }
            });
        addItem(gate);
    }
}

void GraphicsScene::selectedGateTool(const QString& tool) {
    selectedGateTool_ = tool;
}
