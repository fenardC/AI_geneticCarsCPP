#pragma once

#include <string>

#include "DemoMisc/main/inc/CarSensor.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class CarSensorLine final : public CarSensor {
    public:
        CarSensorLine();

    public:
        void check() override ;

    public:
        double getAbsAngle() const ;

    public:
        Vector2D * getAbsPosition() const ;

    public:
        double getAngle() const ;

    public:
        double getValue() const override ;

    public:
        void render(Drawer & drawer) const override ;

    public:
        void setAngle(const double angle) ;

    private:
        double angle;

    private:
        double dist;

    private:
        double value;
};
