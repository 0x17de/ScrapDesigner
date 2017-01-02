#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include "GateHandles.hpp"
#include "GraphicsSvgButton.hpp"


class GraphicsGate;
class QGraphicsRectItem;
class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

    GateHandleMap& gateHandles_;
    QString selectedGateTool_;
    GraphicsGate* lastSelectedGate_;

    QGraphicsItemGroup toolsGroup_;
    GraphicsSvgButton deleteButton_;

public:
    explicit GraphicsScene(QObject* parent, GateHandleMap& gateHandles);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

public Q_SLOTS:
    void selectedGateTool(const QString& name);
    void onMoveSelectedGate(const QPointF& newPosition);

signals:
    void newGate(GraphicsGate* gate);
    void newBoundingRect(const QRectF& rect);
};


#endif
