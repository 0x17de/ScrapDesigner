#ifndef GATEHANDLES_H
#define GATEHANDLES_H

#include <QString>


class GraphicsGate;
class QGraphicsItem;
class QAction;
struct GateHandles {
    QAction* action;
    QString imagePath;

    GateHandles();
    GateHandles(QAction* action,
                const QString& imagePath);
    GraphicsGate* spawn(QGraphicsItem* panel, const QPointF& pos = {0, 0});
};
using GateHandleMap = QHash<QString, GateHandles>;

#endif
