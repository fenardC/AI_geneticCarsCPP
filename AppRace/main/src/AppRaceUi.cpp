
#include "AppRace/main/inc/AppRaceUi.h"
#include "AppRace/main/inc/AppRace.hpp"
#include "ui_AppRace.h"

#include <QPainter>
#include "CoreApp/main/inc/CarMotionHelper.hpp"
#include "Debug/main/inc/Logger.hpp"


AppRaceUi::AppRaceUi(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppRaceUi)
    , racer(nullptr) {
    Logger::debug("AppRaceUi()>");
    ui->setupUi(this);

    racer = new AppRace(this);
    racer->startWorker();

    Logger::debug("AppRaceUi()<");
}

void AppRaceUi::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Drawer drawer(this);
    racer->doWork(drawer);
}

AppRaceUi::~AppRaceUi() {
    racer->stopWorker();
    delete racer;
    delete ui;
    Logger::debug("~AppRaceUi()<");
}
