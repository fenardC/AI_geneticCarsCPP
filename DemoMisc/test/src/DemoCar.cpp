
#include "Debug/main/inc/Logger.hpp"
#include "DemoGui/main/inc/ScreenGeneticCar.hpp"
#include "DemoMisc/test/inc/DemoCar.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Misc/main/inc/Vector2D.hpp"

#include <string>

const double DemoCar::CAR_MILLIS_PER_TICK = 20.0;
const double DemoCar::CAR_RATIO = 0.5;
const int DemoCar::CAR_SENSOR_TYPE = ScreenGeneticCar::TYPE_SENSOR_LINE;
const int DemoCar::TASK_PERFORMER_DELAY_IN_MS = 20;

DemoCar::DemoCar()
    : car(nullptr)
    , command(0) {
    initialize();
}

DemoCar::~DemoCar() {
    delete car;
}

void DemoCar::initialize() {

    Logger::trace("DemoCar::initialize() >");

    car = new Car(std::string("Car_") + std::to_string(0),
                  DemoCar::CAR_SENSOR_TYPE, DemoCar::CAR_RATIO);

    car->setColor(QColor(Qt::red));
    car->setPosition(new Vector2D(150.0, 150.0));
    car->setAngle(90);

    Logger::trace("DemoCar::initialize() <");
}

void DemoCar::moveCar(Drawer & drawer) {

    Logger::trace("DemoCar::moveCar() >");

    /* Update Car with commands */
    const int engineCommand = Misc::mix(-128.0, 128.0, command);
    const int wheelCommand = Misc::mix(-128.0, 128.0, command);
    command++;

    if (command > 128) {
        command = -128;
    }

    car->setEngineCommand(engineCommand);
    car->setWheelCommand(wheelCommand);
    car->testTick(DemoCar::CAR_MILLIS_PER_TICK);
    Logger::debug("DemoCar::moveCar() @ calling car->testRender()");
    car->testRender(drawer);

    Logger::trace("DemoCar::moveCar() <");
}
