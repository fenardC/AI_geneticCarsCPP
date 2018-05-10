#pragma once

#include <string>
#include <cmath>
#include <iostream>


class Vector2D {
    public:
        Vector2D();

    public:
        Vector2D(const double valueX, const double valueY);

    public:
        Vector2D(const Vector2D & other);

    public:
        static Vector2D * add(const Vector2D & vector1, const Vector2D & vector2);

    public:
        static double dot(const Vector2D & vector1, const Vector2D & vector2);

    public:
        static Vector2D * getVector2DFromValueAngle(const double length, const double angleInDegree);

        /**
         * @return Returns vector with a magnitude of 1.
         */
    public:
        static Vector2D * normalize(const Vector2D & vector);

    public:
        static Vector2D * rotate(const Vector2D & vector, const double angleInDegree);

    public:
        static Vector2D * substract(const Vector2D & vector1, const Vector2D & vector2);

    public:
        Vector2D add(const Vector2D & vector);

        /**
         * @return Angle in degree.
         */
    public:
        double getOrientation() const ;

    public:
        double getX() const ;

    public:
        double getY() const ;

        /**
         * @return Returns the length of this vector
         */
    public:
        double length() const;

        /**
         * @return Returns the square of the length of this vector
         */
    public:
        double lengthSquared() const;

    public:
        Vector2D * multiply(const double ratio) const;

    public:
        Vector2D * multiply2(const double ratio) const;

    public:
        std::string toString() const;

    private:
        double x;

    private:
        double y;

    private:
        static const double PI;

    private:
        static const bool DEBUG_ENABLED;
};
