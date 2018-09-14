#include "AppRace/main/inc/AppRaceUi.h"
#include "AppRace/main/inc/AppRace.hpp"
#include "ui_AppRace.h"
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include <QPainter>

AppRaceUi::AppRaceUi(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppRaceUi)
    , racer(nullptr) {
    Logger::trace(std::string("AppRaceUi::AppRaceUi()>"));
    ui->setupUi(this);

    racer = new AppRace(this);
    racer->startWorker();

    Logger::trace(std::string("AppRaceUi::AppRaceUi()<"));
}

void AppRaceUi::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Drawer drawer(this);
    racer->doWork(drawer);
}

AppRaceUi::~AppRaceUi() {
    Logger::trace(std::string("AppRaceUi::~AppRaceUi()>"));
    racer->stopWorker();
    delete racer;
    delete ui;
    Logger::trace(std::string("AppRaceUi::~AppRaceUi()<"));
}
