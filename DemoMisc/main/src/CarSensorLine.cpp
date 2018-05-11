#include "DemoMisc/main/inc/CarSensorLine.hpp"

#include "DemoMisc/main/inc/Car.hpp"
#include "DemoMisc/main/inc/CarSensor.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Vector2D.hpp"

CarSensorLine::CarSensorLine()
    : ::CarSensor()
    , angle(0.0)
    , dist(0.0)
    , value(0.0) {
}

void CarSensorLine::check() {
    const double range = ScreenGeneticCar::SENSOR_LINE_RANGE;
    const Vector2D * absPosition = getAbsPosition();
    const double absAngle = getAbsAngle();

    dist = 0.0;

    for (double myDist = 0.0; myDist <= range; myDist += ScreenGeneticCar::SENSOR_LINE_PRECISION) {
        const Vector2D * delta = Vector2D::getVector2DFromValueAngle(myDist, absAngle);
        const Vector2D * pos = Vector2D::add(*absPosition, *delta);

        delete delta;

        if (car->getTrack()->isPointInTrack(*pos) != -1) {
            dist = myDist;
            delete pos;

        }
        else {
            delete pos;
            break;
        }
    }

    value = dist / 100.0;
    delete absPosition;
}

double CarSensorLine::getAbsAngle() const {
    return car->getAngle() + angle;
}

Vector2D * CarSensorLine::getAbsPosition() const {
    return new Vector2D(*car->getPosition());
}

double CarSensorLine::getAngle() const {
    return angle;
}

double CarSensorLine::getValue() const {
    return value;
}

void CarSensorLine::render(Drawer & drawer) const {
    const Vector2D * pos1 = getAbsPosition();
    const Vector2D * delta = Vector2D::getVector2DFromValueAngle(dist, getAbsAngle());
    const Vector2D * pos2 = Vector2D::add(*pos1, *delta);

    delete delta;

    drawer.setColor(QColor(Qt::blue));
    drawer.drawLine(pos1->getX(), pos1->getY(), pos2->getX(), pos2->getY());

    delete pos1;
    delete pos2;
}

void CarSensorLine::setAngle(const double angle) {
    this->angle = angle;
}

