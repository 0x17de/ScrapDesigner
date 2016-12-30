#include <QAction>
#include "GateHandles.hpp"
#include "GraphicsGate.hpp"


GateHandles::GateHandles() = default;
GateHandles::GateHandles(QAction* action,
            const QString& imagePath)
    : action{action}
    , imagePath{imagePath}
{ }
GraphicsGate* GateHandles::spawn(QGraphicsItem* panel, const QPointF& pos) {
    GraphicsGate* gate = new GraphicsGate(imagePath, panel);
    QRectF bounds = gate->boundingRect();
    gate->setPos(pos - bounds.center());
    return gate;
}
