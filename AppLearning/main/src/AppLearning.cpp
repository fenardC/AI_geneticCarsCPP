#include "AppLearning/main/inc/AppLearning.hpp"
#include "AppLearning/main/inc/CarsLearningWorker.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Misc.hpp"

const std::string AppLearning::FONT_VERDANA = "Verdana";

AppLearning::AppLearning(AppLearningUi * mainUi)
    : worker(new CarsLearningWorker(mainUi)) {

    initialize();
}

void AppLearning::initialize() {

}

void AppLearning::doWork(Drawer & drawer) {
    worker->doWork(drawer);
}

void AppLearning::startWorker() {
    worker->startRunning();
}
