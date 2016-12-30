#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include "GraphicsScene.hpp"
#include "moc_GraphicsScene.cpp"
#include "GraphicsGate.hpp"


GraphicsScene::GraphicsScene(QObject* parent, GateHandleMap& gateHandles)
    : QGraphicsScene(parent)
    , gateHandles_{gateHandles}
{ }

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
                    QRectF oldRect = selection_->rect();
                    selection_->setRect(rect);
                    invalidate(oldRect);
                }
            });
        addItem(gate);

        emit newGate(gate);
    }
}

void GraphicsScene::selectedGateTool(const QString& tool) {
    selectedGateTool_ = tool;
}
