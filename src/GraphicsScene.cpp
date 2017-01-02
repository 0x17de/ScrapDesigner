#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include "GraphicsScene.hpp"
#include "moc_GraphicsScene.cpp"
#include "GraphicsGate.hpp"


GraphicsScene::GraphicsScene(QObject* parent, GateHandleMap& gateHandles)
    : QGraphicsScene(parent)
    , gateHandles_{gateHandles}
    , lastSelectedGate_{0}
    , deleteButton_(":/images/Octagon_delete.svg")
{;
    deleteButton_.setPos(-10+40, -10-30);
    deleteButton_.setScale(0.5);
    deleteButton_.setZValue(50);
    toolsGroup_.addToGroup(&deleteButton_);
    toolsGroup_.setZValue(50);
    toolsGroup_.hide();
    addItem(&toolsGroup_);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (deleteButton_.isUnderMouse()) {
        if (lastSelectedGate_) {
            delete lastSelectedGate_;
            lastSelectedGate_ = 0;
        }
        return;
    }
    QGraphicsScene::mousePressEvent(event);

    if (!event->isAccepted() && gateHandles_.contains(selectedGateTool_)) {
        GraphicsGate* gate = gateHandles_[selectedGateTool_].spawn(activePanel(), event->lastScenePos());

        connect(this, &QGraphicsScene::selectionChanged, [this]{
                QList<GraphicsGate*> gates;
                auto items = selectedItems();
                for (auto* item : items) {
                    GraphicsGate* gate = dynamic_cast<GraphicsGate*>(item);
                    if (gate != nullptr)
                        gates.append(gate);
                }

                if (lastSelectedGate_) {
                    disconnect(lastSelectedGate_, &GraphicsGate::gateMoved, this, &GraphicsScene::onMoveSelectedGate);
                    lastSelectedGate_ = 0;
                }
                if (gates.count() == 0) {
                    toolsGroup_.hide();
                } else {
                    toolsGroup_.show();
                    lastSelectedGate_ = gates.last();
                    connect(lastSelectedGate_, &GraphicsGate::gateMoved, this, &GraphicsScene::onMoveSelectedGate);
                    onMoveSelectedGate(lastSelectedGate_->pos() + lastSelectedGate_->boundingRect().center());
                }
            });
        addItem(gate);

        emit newGate(gate);
    }
}

void GraphicsScene::selectedGateTool(const QString& tool) {
    selectedGateTool_ = tool;
}

void GraphicsScene::onMoveSelectedGate(const QPointF& newPosition) {
    toolsGroup_.setPos(newPosition);
}
