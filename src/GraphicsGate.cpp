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

QVariant GraphicsGate::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        auto newPos = value.toPointF();
        QRectF gateRect = boundingRect();
        emit gateMoved(newPos + gateRect.center());
        // return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
