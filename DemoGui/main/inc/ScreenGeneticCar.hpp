#pragma once

class ScreenGeneticCar {
    public:
        static const int TYPE_SENSOR_POINT;

    public:
        static const int TYPE_SENSOR_LINE;

        /* Eight sensors per car. */
    public:
        static const int SENSOR_LINE_NUMBER;

    public:
        static const double SENSOR_LINE_ANGLE_COVER;

    public:
        static const double SENSOR_LINE_RANGE;

    public:
        static const double SENSOR_LINE_PRECISION;

        /* Not relevant since TYPE_SENSOR_LINE in use. */
    public:
        static const int SENSOR_X;

    public:
        static const int SENSOR_Y;

    private:
        ScreenGeneticCar() {
        }
};
