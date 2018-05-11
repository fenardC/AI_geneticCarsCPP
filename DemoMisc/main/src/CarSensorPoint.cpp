
#include "DemoMisc/main/inc/CarSensorPoint.hpp"
#include "DemoMisc/main/inc/Car.hpp"

CarSensorPoint::CarSensorPoint()
    : ::CarSensor()
    , offset(nullptr)
    , value(false)
    , lastIndexTriangle(0) {
}

CarSensorPoint::~CarSensorPoint() {
    delete offset;
}

void CarSensorPoint::check() {
    value = false;
    const Vector2D * pos = getAbsPosition();

    lastIndexTriangle = CarSensor::car->getTrack()->isPointInTrack(*pos);

    if (lastIndexTriangle != -1) {
        value = true;
    }

    delete pos;
}

Vector2D * CarSensorPoint::getAbsPosition() const {
    const Vector2D carPos(*car->getPosition());
    const Vector2D * const rotate = Vector2D::rotate(*offset, car->getAngle());
    const Vector2D * const sensorPos = rotate->multiply(car->getRatio());
    Vector2D * result = Vector2D::add(carPos, *sensorPos);
    delete sensorPos;
    delete rotate;

    return result;
}

int CarSensorPoint::getLastIndexTriangle() const {
    return lastIndexTriangle;
}

double CarSensorPoint::getValue() const  {
    return value ? 1.0 : 0.0;
}

void CarSensorPoint::render(Drawer & drawer) const {
    const Vector2D * pos = getAbsPosition();
    drawer.setColor(value ? QColor(Qt::blue) : QColor(Qt::red));
    drawer.drawRect(pos->getX(), pos->getY(), 3, 3);
    delete pos;
}

void CarSensorPoint::setOffset(const Vector2D & offset) {
    delete this->offset;
    this->offset = new Vector2D(offset);
}
