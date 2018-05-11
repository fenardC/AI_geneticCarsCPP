#include "Draw/test/inc/AppTestDraw.h"
#include "Draw/test/inc/TestDraw.hpp"
#include "ui_AppTestDraw.h"
#include <QPainter>
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"

AppTestDraw::AppTestDraw(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::AppTestDraw) {
    ui->setupUi(this);
    // this->setStyleSheet("background-color: black;");
}

void AppTestDraw::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Logger::debug("paintEvent()>");

    Drawer drawer(this);

    TestDraw tester;
    tester.testDraw(drawer);

    Logger::debug("paintEvent()<");
}

AppTestDraw::~AppTestDraw() {
    delete ui;
}
