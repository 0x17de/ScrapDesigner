#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QAction>
#include <QString>
#include <QGraphicsSvgItem>

#include "GateHandles.hpp"
#include "GraphicsView.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsGate.hpp"


template<class T>
struct GateHandleInitializer {
    T& map_;
    QToolBar* toolBar_;
    QActionGroup* actionGroup_;
    GraphicsScene* scene_;

    GateHandleInitializer(T& map, QToolBar* toolBar, QActionGroup* actionGroup, GraphicsScene* scene)
        : map_{map}
        , toolBar_{toolBar}
        , actionGroup_{actionGroup}
        , scene_{scene}
    { }

    void addGate(const QString& name) {
        QString lowerName = name.toLower();
        GraphicsScene* scene = scene_;
        QAction* action = toolBar_->addAction(name);
        action->setCheckable(true);
        action->setActionGroup(actionGroup_);
        action->connect(action, &QAction::toggled, [scene, lowerName](bool checked) {
                if (checked)
                    scene->selectedGateTool(lowerName);
            });
        map_.insert(lowerName, GateHandles(action,
                                               QString(":/images/gates/")+name+"_ANSI.svg"));
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("popup_ScrapDesigner");
    window.resize(600, 400);

    QWidget* central = new QWidget(&window);
    window.setCentralWidget(central);

    QToolBar* gatesToolBar = new QToolBar(central);
    window.addToolBar(Qt::LeftToolBarArea, gatesToolBar);

    QActionGroup* gatesGroup = new QActionGroup(gatesToolBar);
    GateHandleMap gateHandles;

    GraphicsScene* scene = new GraphicsScene(central, gateHandles);

    GateHandleInitializer<decltype(gateHandles)> gateHandleInitializer(gateHandles, gatesToolBar, gatesGroup, scene);
    for (const char* c : {"NOT", "AND", "OR", "NAND", "NOR", "XNOR", "XOR"})
        gateHandleInitializer.addGate(c);
    gateHandles["not"].action->setChecked(true);

    QVBoxLayout* vbox = new QVBoxLayout(central);
    GraphicsView* view = new GraphicsView(scene, central);
    vbox->addWidget(view);

    central->setLayout(vbox);
    window.show();

    return app.exec();
}
