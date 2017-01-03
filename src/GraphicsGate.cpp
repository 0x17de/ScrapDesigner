#include "GraphicsGate.hpp"
#include "moc_GraphicsGate.cpp"
#include <QGraphicsRectItem>


GraphicsGate::GraphicsGate(const QString& path, QGraphicsItem* parent)
    : QGraphicsSvgItem(path, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

GraphicsGate::~GraphicsGate() {
    for (auto t : connections) {
        GraphicsGate* gate = std::get<1>(t);
        disconnectOther(gate);
    }
    connections.clear();
}

QVariant GraphicsGate::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        auto newPos = value.toPointF();
        QRectF gateRect = boundingRect();

        QPointF pos = newPos + gateRect.center();
        updateConnections();

        emit gateMoved(pos);
        // return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsGate::updateConnections() {
    QPointF newPos = pos();
    for (auto& t : connections) {
        QGraphicsLineItem* connection = std::get<0>(t);
        GraphicsGate* other = std::get<1>(t);
        QLineF line = connection->line();
        line.setP2(other->pos() + other->boundingRect().center() - QPointF(44, 0) - newPos);
        connection->setLine(line);
    }
}

void GraphicsGate::onOtherDestroyed(QObject* other) {
    for (auto it = connections.begin(); it != connections.end();) {
        GraphicsGate* gate = std::get<1>(*it);
        if (other == gate) {
            QGraphicsLineItem* item = std::get<0>(*it);
            item->setParentItem(0);
            delete item;
            it = connections.erase(it);
        } else {
            ++it;
        }
    }
}

void GraphicsGate::onOtherMoved(const QPointF& other) {
    updateConnections();
}

void GraphicsGate::disconnectOther(GraphicsGate* other) {
    disconnect(other, &GraphicsGate::gateMoved, this, &GraphicsGate::onOtherMoved);
    disconnect(other, &QObject::destroyed, this, &GraphicsGate::onOtherDestroyed);
}

void GraphicsGate::connectTo(GraphicsGate* other) {
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(boundingRect().center()+QPoint(44, 0), QPointF()), this);

    connections.append(std::make_tuple(line, other));
    connect(other, &GraphicsGate::gateMoved, this, &GraphicsGate::onOtherMoved);
    connect(other, &QObject::destroyed, this, &GraphicsGate::onOtherDestroyed);

    updateConnections();
}
