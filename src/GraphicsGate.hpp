#ifndef GRAPHICSGATE_H
#define GRAPHICSGATE_H

#include <QGraphicsSvgItem>
#include <QList>
#include <tuple>


class QVariant;
class QGraphicsLineItem;
class GraphicsGate : public QGraphicsSvgItem {
    Q_OBJECT

    using Connection = std::tuple<QGraphicsLineItem*, GraphicsGate*>;
    QList<Connection> connections;

public:
    explicit GraphicsGate(const QString& path, QGraphicsItem* parent);
    ~GraphicsGate();
    void connectTo(GraphicsGate* other);
    void disconnectOther(GraphicsGate* other);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateConnections();

public Q_SLOTS:
    void onOtherMoved(const QPointF& location);
    void onOtherDestroyed(QObject* other);

signals:
    void gateMoved(const QPointF& newPosition);
};


#endif
