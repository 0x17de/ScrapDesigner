#include "GraphicsGate.hpp"
#include "moc_GraphicsGate.cpp"


GraphicsGate::GraphicsGate(const QString& path, QGraphicsItem* parent)
    : QGraphicsSvgItem(path, parent)
{ }

void GraphicsGate::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    selected(this);
}
