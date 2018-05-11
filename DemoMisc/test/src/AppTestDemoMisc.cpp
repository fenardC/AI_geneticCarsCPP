
#include "DemoMisc/test/inc/AppTestDemoMisc.h"
#include "ui_AppTestDemoMisc.h"

#include <QPainter>
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"


AppTestDemoMisc::AppTestDemoMisc(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppTestDemoMisc)
    , timer(new QTimer(this))
    , demo(nullptr) {

    Logger::debug("AppTestDemoMisc()>");
    ui->setupUi(this);

    demo = new DemoCar();

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(DemoCar::CAR_MILLIS_PER_TICK);

    Logger::debug("AppTestDemoMisc()<");
}

void AppTestDemoMisc::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Logger::debug("paintEvent()>");

    Drawer drawer(this);
    drawer.setColor(QColor(Qt::white));
    drawer.drawRect(10.0, 10.0, 50, 25);
    drawer.setColor(QColor(Qt::green));
    drawer.drawString("Command : " + std::to_string(demo->getCommand()), 10, 70);
    demo->moveCar(drawer);

    Logger::debug("paintEvent()<");
}

AppTestDemoMisc::~AppTestDemoMisc() {
    Logger::debug("~AppTest()<");

    timer->stop();
    delete timer;
    delete demo;
    delete ui;
}
