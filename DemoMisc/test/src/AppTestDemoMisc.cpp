#include "Debug/main/inc/Logger.hpp"
#include "DemoMisc/test/inc/AppTestDemoMisc.h"
#include "Draw/main/inc/Drawer.hpp"
#include "ui_AppTestDemoMisc.h"
#include <QPainter>

AppTestDemoMisc::AppTestDemoMisc(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppTestDemoMisc)
    , timer(new QTimer(this))
    , demo(nullptr) {

    Logger::trace(std::string("AppTestDemoMisc::AppTestDemoMisc()>"));
    ui->setupUi(this);

    demo = new DemoCar();

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(DemoCar::CAR_MILLIS_PER_TICK);

    Logger::trace(std::string("AppTestDemoMisc::AppTestDemoMisc()<"));
}

void AppTestDemoMisc::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Logger::trace(std::string("AppTestDemoMisc::paintEvent()>"));

    Drawer drawer(this);
    drawer.setColor(QColor(Qt::white));
    drawer.drawRect(10.0, 10.0, 50, 25);
    drawer.setColor(QColor(Qt::green));
    drawer.drawString(std::string("Command : ") + std::to_string(demo->getCommand()), 10, 70);
    demo->moveCar(drawer);

    Logger::trace(std::string("AppTestDemoMisc::paintEvent()<"));
}

AppTestDemoMisc::~AppTestDemoMisc() {
    Logger::trace(std::string("AppTestDemoMisc~AppTestDemoMisc()<"));

    timer->stop();
    delete timer;
    delete demo;
    delete ui;
}
