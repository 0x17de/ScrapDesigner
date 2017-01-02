#include "GraphicsSvgButton.hpp"
#include "moc_GraphicsSvgButton.cpp"
#include <QGraphicsSceneMouseEvent>


GraphicsSvgButton::GraphicsSvgButton(const QString& path, QGraphicsItem* parent)
    : QGraphicsSvgItem(path, parent)
{ }

void GraphicsSvgButton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    event->accept();
    emit clicked();
}
