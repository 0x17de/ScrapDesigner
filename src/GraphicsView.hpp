#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>


class GraphicsScene;
class GraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    GraphicsView(GraphicsScene* scene, QWidget* parent);

protected:
    const int padding = 100;

    void fixSceneRect(const QSizeF& newSize = {});
    virtual void resizeEvent(QResizeEvent* event) override;
};


#endif
