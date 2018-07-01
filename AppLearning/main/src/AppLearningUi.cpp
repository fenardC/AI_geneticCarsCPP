
#include "AppLearning/main/inc/AppLearningUi.h"
#include "AppLearning/main/inc/AppLearning.hpp"
#include "CoreApp/main/inc/CarMotionHelper.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "ui_AppLearning.h"

#include <QPainter>

AppLearningUi::AppLearningUi(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppLearningUi)
    , learner(nullptr) {
    Logger::trace("AppLearningUi()>");

    ui->setupUi(this);

    learner = new AppLearning(this);
    learner->startWorker();

    Logger::trace("AppLearningUi()<");
}

void AppLearningUi::paintEvent(QPaintEvent * e) {
    QMainWindow::paintEvent(e);

    Drawer drawer(this);
    learner->doWork(drawer);
}

AppLearningUi::~AppLearningUi() {
    Logger::trace("~AppLearningUi()<");
    delete ui;
}
