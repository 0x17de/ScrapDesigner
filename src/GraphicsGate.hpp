#ifndef GRAPHICSGATE_H
#define GRAPHICSGATE_H

#include <QGraphicsSvgItem>


class GraphicsGate : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit GraphicsGate(const QString& path, QGraphicsItem* parent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void selected(GraphicsGate* gate);
};


#endif
