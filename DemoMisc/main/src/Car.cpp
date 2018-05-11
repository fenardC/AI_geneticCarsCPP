#include "DemoMisc/main/inc/Car.hpp"

#include <map>

#include "DemoGui/main/inc/ScreenGeneticCar.hpp"
#include "DemoMisc/main/inc/CarSensor.hpp"
#include "DemoMisc/main/inc/CarSensorLine.hpp"
#include "DemoMisc/main/inc/CarSensorPoint.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/Texture.hpp"
#include "Draw/main/inc/TextureModifier.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Debug/main/inc/Debugger.hpp"

Car::Car(std::string name, int typeSensor, double ratio)
    : name(name)
    , maxIndexTriangleDiff(10)
    , track(nullptr)
    , indiv(nullptr)
    , mapRoadSensor()
    , listRoadCollision()
    , wheelCommand(0)
    , engineCommand(0)
    , engine(0)
    , acceleration(128.0)
    , position(nullptr)
    , angle(0.0)
    , ratio(ratio)
    , textureModifier(nullptr)
    , bestIndexSpline(0)
    , lap(0)
    , timeLap(0.0)
    , color() {

    Texture::init();

    textureModifier = new TextureModifier();

    const double w = 50.0;
    const double h = 25.0;

    addRoadCollision(Vector2D(w, h));
    addRoadCollision(Vector2D(w, -h));
    addRoadCollision(Vector2D(-w, h));
    addRoadCollision(Vector2D(-w, -h));

    if (typeSensor == ScreenGeneticCar::TYPE_SENSOR_POINT) {
        Vector2D offset(70.0, 0.0);
        Vector2D size(40.0, 40.0);

        for (int i = 0; i < ScreenGeneticCar::SENSOR_X; i++) {
            for (int j = 0; j < ScreenGeneticCar::SENSOR_Y; j++) {
                int a = j - static_cast<int>(std::floor(static_cast<float>(ScreenGeneticCar::SENSOR_Y / 2.0)));
                CarSensorPoint * sensor = new CarSensorPoint();
                Vector2D offsetXY(i * size.getX(), a * size.getY());
                sensor->setCar(this);
                sensor->setOffset(offsetXY);
                mapRoadSensor[std::string("s") + std::to_string(i) + "_" + std::to_string(j)] = sensor;
            }
        }
    }
    else {
        for (int i = 0; i < ScreenGeneticCar::SENSOR_LINE_NUMBER; i++) {
            CarSensorLine * sensor = new CarSensorLine();
            sensor->setCar(this);
            sensor->setAngle(i / (double)(ScreenGeneticCar::SENSOR_LINE_NUMBER - 1) *
                             ScreenGeneticCar::SENSOR_LINE_ANGLE_COVER -
                             ScreenGeneticCar::SENSOR_LINE_ANGLE_COVER / 2);
            mapRoadSensor[std::string("s") + std::to_string(i)] = sensor;
        }
    }

    textureModifier->setCenter(50, 25);
    textureModifier->setAntialiasing(TextureModifier::ANTIALIASING_HIGH);
}

Car::~Car() {
    {
        auto deleteSensor = [](std::pair<std::string, const CarSensor *> pair) { delete pair.second; };
        std::for_each(mapRoadSensor.begin(), mapRoadSensor.end(), deleteSensor);
        mapRoadSensor.clear();
    }
    {
        auto deleteSensorPoint = [](const CarSensorPoint * p) { delete p; };
        std::for_each(listRoadCollision.begin(), listRoadCollision.end(), deleteSensorPoint);
        listRoadCollision.clear();
    }
    delete position;
    delete textureModifier;
}

void Car::addRoadCollision(const Vector2D & offset) {
    CarSensorPoint * sensor = new CarSensorPoint();
    sensor->setCar(this);
    sensor->setOffset(offset);
    listRoadCollision.push_back(sensor);
}

double Car::getAngle() const {
    return angle;
}

QColor Car::getColor() const {
    return color;
}

int Car::getEngine() const {
    return engine;
}

int Car::getEngineCommand() const {
    return engineCommand;
}

GeneticIndividual * Car::getIndiv() const {
    return indiv;
}

int Car::getLap() const {
    return lap;
}

std::string Car::getName() const {
    return name;
}

Vector2D * Car::getPosition() const {
    return position;
}

double Car::getRatio() const {
    return ratio;
}

double Car::getSensorValue(const std::string & name) const {
    const auto search = mapRoadSensor.find(name);

    if (search != mapRoadSensor.end()) {
        return search->second->getValue();
    }

    return 0.0;
}

double Car::getTimeLap() const {
    return timeLap;
}

Track * Car::getTrack() const {
    return track;
}

double Car::getTrackPercentCompletion() const {
    return 100.0 * bestIndexSpline / (double) track->getListTriangle().size();
}

int Car::getWheelCommand() const {
    return wheelCommand;
}

bool Car::isOnTrack() const {
    int nb = 0;

    for (const CarSensorPoint * sensor : listRoadCollision) {
        if (sensor->getValue() > 0) {
            nb++;

            if (nb >= 3) {
                return true;
            }
        }
    }

    return false;
}

void Car::putOnTrack(Track * const track) {
    this->track = track;
    this->position = new Vector2D(*track->getSpline()->getListResultPoint()[0]);
    /* Start in the same direction as the index of the list grows !!!!!! */
    this->angle = track->getSpline()->getListResultPerpendicular()[0]->getOrientation() - 90.0;
}

void Car::render(Drawer & d) const {
    renderCarOnly(d);

    if (Debugger::isDebugEnabled("sensor")) {
        for (const CarSensorPoint * sensor : listRoadCollision) {
            sensor->render(d);
        }

        for (auto it = mapRoadSensor.begin(); it != mapRoadSensor.end(); ++it) {
            it->second->render(d);
        }
    }
}

void Car::renderCarOnly(Drawer & d) const {
    textureModifier->setAngle(angle);
    textureModifier->setRatio(ratio);

    textureModifier->setColor(color);

    Texture::draw(d, position->getX(), position->getY(), *textureModifier);
}

void Car::setAngle(double angle) {
    this->angle = angle;
}

void Car::setBestIndexSpline(int bestIndexSpline) {
    this->bestIndexSpline = bestIndexSpline;
}

void Car::setColor(QColor color) {
    this->color = color;
}

void Car::setEngineCommand(int engineCommand) {
    this->engineCommand = engineCommand;
}

void Car::setIndiv(GeneticIndividual * indiv) {
    this->indiv = indiv;
}

void Car::setLap(int lap) {
    this->lap = lap;
}

void Car::setPosition(Vector2D * position) {
    delete this->position;
    this->position = position;
}

void Car::setRatio(double ratio) {
    this->ratio = ratio;
}

void Car::setTimeLap(double timeLap) {
    this->timeLap = timeLap;
}

void Car::setTrack(Track * track) {
    this->track = track;
}

void Car::setWheelCommand(int wheelCommand) {
    this->wheelCommand = wheelCommand;
}

void Car::testRender(Drawer & d) const {
    renderCarOnly(d);
}

void Car::testTick(double millis) {
    tickCarOnly(millis);
}

void Car::tick(double millis) {

    tickCarOnly(millis);

    /* Update Sensors */
    for (CarSensorPoint * sensor : listRoadCollision) {
        sensor->tick();
        const int sensorLastIndexTriangle = sensor->getLastIndexTriangle();

        if (sensorLastIndexTriangle > -1) {
            if (sensorLastIndexTriangle > bestIndexSpline &&
                    sensorLastIndexTriangle <= bestIndexSpline + maxIndexTriangleDiff) {
                bestIndexSpline = sensorLastIndexTriangle;
            }
            else if (sensorLastIndexTriangle <= maxIndexTriangleDiff &&
                     track->getListTriangle().size() <= bestIndexSpline + maxIndexTriangleDiff) {
                bestIndexSpline = sensorLastIndexTriangle;
                lap++;
            }
        }
    }

    for (auto it = mapRoadSensor.begin(); it != mapRoadSensor.end(); ++it) {
        it->second->tick();
    }
}

void Car::tickCarOnly(double millis) {
    const double m = millis / 1000;
    const double ratioWheel = Misc::bound(wheelCommand / 128.0, -1, 1);
    const double accel = acceleration * m;

    if (engineCommand > engine) {
        if (engineCommand > engine + accel) {
            engine += accel;
        }
        else {
            engine = engineCommand;
        }
    }
    else if (engineCommand < engine) {
        if (engineCommand < engine - accel) {
            engine -= accel;
        }
        else {
            engine = engineCommand;
        }
    }

    const double ratioEngine = Misc::bound(engine / 128.0, -1, 1);

    /* Move Car */
    if (ratioEngine >= 0) {
        angle = angle + ratioWheel * (0.5 + 0.5 * ratioEngine) * 180 * m;
    }
    else {
        angle = angle + ratioWheel * (-0.5 + 0.5 * ratioEngine) * 180 * m;
    }

    const Vector2D * const fromCommands = Vector2D::getVector2DFromValueAngle(ratioEngine * 300 * m, angle);
    position->add(*fromCommands);
    delete fromCommands;
}
