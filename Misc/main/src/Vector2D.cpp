#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/Vector2D.hpp"

Vector2D::Vector2D()
    : Vector2D(0, 0) {
}

Vector2D::Vector2D(const double valueX, const double valueY)
    : x(valueX)
    , y(valueY) {
    if (Vector2D::DEBUG_ENABLED) {
        Logger::debug(toString());
    }
}

Vector2D::Vector2D(const Vector2D & other)
    : x(other.x)
    , y(other.y) {
    if (Vector2D::DEBUG_ENABLED) {
        Logger::debug(toString());
    }
}

Vector2D::~Vector2D() {
    x = 0;
    y = 0;
}

Vector2D * Vector2D::add(const Vector2D & vector1, const Vector2D & vector2) {
    return new Vector2D(vector1.x + vector2.x, vector1.y + vector2.y);
}

double Vector2D::dot(const Vector2D & vector1, const Vector2D & vector2) {
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

Vector2D * Vector2D::getVector2DFromValueAngle(const double length, const double angleInDegree)  {
    double angle = (Vector2D::PI * angleInDegree) / 180.0;
    return new Vector2D(length * cos(angle), length * sin(angle));
}

/**
 * @return Returns vector with a magnitude of 1.
 */
Vector2D * Vector2D::normalize(const Vector2D & vector) {
    const double length = vector.length();
    Vector2D * result;

    if (length != 0) {
        result = new Vector2D(vector.x / length, vector.y / length);
    }
    else {
        result = new Vector2D(0, 0);
    }

    return result;
}

Vector2D * Vector2D::rotate(const Vector2D & vector, const double angleInDegree) {
    double angle = (Vector2D::PI * angleInDegree) / 180;
    return new Vector2D((vector.x * cos(angle)) - (vector.y * sin(angle)),
                        (vector.x * sin(angle)) + (vector.y * cos(angle)));
}

Vector2D * Vector2D::substract(const Vector2D & vector1, const Vector2D & vector2) {
    return new Vector2D(vector1.x - vector2.x, vector1.y - vector2.y);
}

Vector2D Vector2D::add(const Vector2D & vector) {
    x = x + vector.x;
    y = y + vector.y;
    return *this;
}

/**
 * @return Angle in degree.
 */
double Vector2D::getOrientation() const {
    return (atan2(y, x) * 180 / Vector2D::PI);
}

double Vector2D::getX() const {
    return x;
}

double Vector2D::getY() const {
    return y;
}

//    public Vector2D Vector2D::multiply(double ratio) {
//        const double angle = getOrientation();
//        const Vector2D result = getVector2DFromValueAngle(ratio * length(), angle);
//        return new Vector2D(result);
//    }

/**
 * @return Returns the length of this vector
 */
double Vector2D::length() const {
    return sqrt(lengthSquared());
}

/**
 * @return Returns the square of the length of this vector
 */
double Vector2D::lengthSquared() const {
    return x * x + y * y;
}

Vector2D * Vector2D::multiply(const double ratio) const {
    return this->multiply2(ratio);
}

Vector2D * Vector2D::multiply2(const double ratio) const {
    return new Vector2D(x * ratio, y * ratio);
}

std::string Vector2D::toString() const {
    std::string result = std::string("Vector2D(");
    result +=  std::to_string(x) + std::string(", ") + std::to_string(y);
    result +=  std::string(")");
    return result;
}

const bool Vector2D::DEBUG_ENABLED = false;

const double Vector2D::PI = 3.14159265358979323846;
