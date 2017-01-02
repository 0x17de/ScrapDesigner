#ifndef GRAPHICSSVGBUTTON_H
#define GRAPHICSSVGBUTTON_H

#include <QGraphicsSvgItem>


class GraphicsSvgButton : public QGraphicsSvgItem {
    Q_OBJECT

public:
    GraphicsSvgButton(const QString& path, QGraphicsItem* parent = Q_NULLPTR);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void clicked();
};


#endif
