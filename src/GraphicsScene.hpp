#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "GateHandleMap.hpp"


class GraphicsGate;
class QGraphicsItemGroup;
class QGraphicsLineItem;
class QGraphicsEllipseItem;
class QGraphicsSvgItem;
class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

    GateHandleMap& gateHandles_;
    QString selectedGateTool_;
    GraphicsGate* lastSelectedGate_;
    GraphicsGate* connectionDragSource_;
    QGraphicsLineItem* connectionIndicator_;

    QGraphicsItemGroup* toolsGroup_;
    QGraphicsEllipseItem* newConnectionButton_;
    QGraphicsSvgItem* deleteButton_;

public:
    explicit GraphicsScene(QObject* parent, GateHandleMap& gateHandles);
    virtual ~GraphicsScene();

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

public Q_SLOTS:
    void selectedGateTool(const QString& name);
    void onMoveSelectedGate(const QPointF& newPosition);

signals:
    void newGate(GraphicsGate* gate);
    void newBoundingRect(const QRectF& rect);
};


#endif
