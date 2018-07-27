#include "AppRace/main/inc/AppRace.hpp"
#include "AppRace/main/inc/CarRacingWorker.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Misc.hpp"

const std::string AppRace::FONT_VERDANA = "Verdana";

AppRace::AppRace(AppRaceUi * mainUi)
    : worker(new CarRacingWorker(mainUi)) {
    initialize();
}

AppRace::~AppRace() {
    std::ostringstream address;
    address << static_cast<void const *>(worker);
    Logger::debug("~AppRace(): worker: " + address.str());

    delete worker;
}

void AppRace::initialize() {
}

void AppRace::doWork(Drawer & drawer) {
    worker->doWork(drawer);
}

void AppRace::startWorker() {
    worker->startRunning();
}

void AppRace::stopWorker() {
    worker->stopRunning();
}
