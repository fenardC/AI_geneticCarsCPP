#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/test/inc/AppTestDraw.h"
#include "Draw/test/inc/TestDraw.hpp"
#include "ui_AppTestDraw.h"
#include <QPainter>

AppTestDraw::AppTestDraw(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::AppTestDraw) {
    ui->setupUi(this);
}

void AppTestDraw::paintEvent(QPaintEvent * /*e*/) {
    Logger::trace(std::string("paintEvent()>"));

    Drawer drawer(this);

    TestDraw tester;
    tester.testDraw(drawer);

    Logger::trace(std::string("paintEvent()<"));
}

AppTestDraw::~AppTestDraw() {
    delete ui;
}
