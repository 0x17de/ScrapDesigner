#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "GateHandles.hpp"


class QGraphicsRectItem;
class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

    GateHandleMap& gateHandles_;
    QGraphicsRectItem* selection_ = 0;
    QString selectedGateTool_;

public:
    explicit GraphicsScene(QObject* parent, GateHandleMap& gateHandles);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

public Q_SLOTS:
    void selectedGateTool(const QString& name);
};


#endif
