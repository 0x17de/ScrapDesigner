#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include "GraphicsScene.hpp"
#include "moc_GraphicsScene.cpp"
#include "GateHandles.hpp"
#include "GraphicsGate.hpp"


GraphicsScene::GraphicsScene(QObject* parent, GateHandleMap& gateHandles)
    : QGraphicsScene(parent)
    , gateHandles_{gateHandles}
    , lastSelectedGate_{0}
    , connectionDragSource_{0}
    , connectionIndicator_{0}
    , toolsGroup_(new QGraphicsItemGroup(activePanel()))
    , newConnectionButton_(new QGraphicsEllipseItem(QRect(0, 0, 11, 11), toolsGroup_))
    , deleteButton_(new QGraphicsSvgItem(":/images/Octagon_delete.svg", toolsGroup_))
{
    newConnectionButton_->setPos(-6+44, -6);
    deleteButton_->setPos(-10+40, -10-30);
    deleteButton_->setScale(0.5);
    toolsGroup_->addToGroup(newConnectionButton_);
    toolsGroup_->addToGroup(deleteButton_);
    toolsGroup_->setZValue(50);
    toolsGroup_->hide();
    addItem(toolsGroup_);
}

GraphicsScene::~GraphicsScene() {
    for (auto& item : selectedItems())
        item->setSelected(false); // would crash otherwise -> mousePressEvent after destructor call
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mouseMoveEvent(event);

    if (connectionIndicator_) {
        QLineF line = connectionIndicator_->line();
        line.setP2(event->scenePos());
        connectionIndicator_->setLine(line);
    }
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mouseReleaseEvent(event);

    if (connectionIndicator_) {
        delete connectionIndicator_;
        connectionIndicator_ = 0;
    }
    if (connectionDragSource_) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform{});
        GraphicsGate* gate = dynamic_cast<GraphicsGate*>(item);
        if (gate)
            connectionDragSource_->connectTo(gate);
        connectionDragSource_ = 0;
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (deleteButton_->isUnderMouse()) {
        if (lastSelectedGate_) {
            delete lastSelectedGate_;
            lastSelectedGate_ = 0;
        }
    } else if (newConnectionButton_->isUnderMouse()) {
        if (lastSelectedGate_) {
            connectionDragSource_ = lastSelectedGate_;
            QLineF line(event->scenePos(), event->scenePos());
            connectionIndicator_ = new QGraphicsLineItem(line, activePanel());
            connectionIndicator_->setZValue(-50);
            addItem(connectionIndicator_);
        }
    } else {
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
                        toolsGroup_->hide();
                    } else {
                        toolsGroup_->show();
                        lastSelectedGate_ = gates.last();
                        connect(lastSelectedGate_, &GraphicsGate::gateMoved, this, &GraphicsScene::onMoveSelectedGate);
                        onMoveSelectedGate(lastSelectedGate_->pos() + lastSelectedGate_->boundingRect().center());
                    }
                });
            addItem(gate);

            emit newGate(gate);
        }
    }
}

void GraphicsScene::selectedGateTool(const QString& tool) {
    selectedGateTool_ = tool;
}

void GraphicsScene::onMoveSelectedGate(const QPointF& newPosition) {
    toolsGroup_->setPos(newPosition);
}
