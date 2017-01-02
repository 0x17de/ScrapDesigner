#ifndef GRAPHICSGATE_H
#define GRAPHICSGATE_H

#include <QGraphicsSvgItem>
#include <QVariant>


class GraphicsGate : public QGraphicsSvgItem {
    Q_OBJECT

public:
    explicit GraphicsGate(const QString& path, QGraphicsItem* parent);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

signals:
    void gateMoved(const QPointF& newPosition);
};


#endif
