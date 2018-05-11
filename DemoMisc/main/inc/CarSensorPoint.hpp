#pragma once

#include <string>

#include "DemoMisc/main/inc/CarSensor.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Misc/main/inc/Vector2D.hpp"

class CarSensorPoint final : public CarSensor {
    public:
        CarSensorPoint();

    public:
        ~CarSensorPoint();

    public:
        void check() override;

    public:
        Vector2D * getAbsPosition() const;

    public:
        int getLastIndexTriangle() const;

    public:
        double getValue() const override;

    public:
        void render(Drawer & drawer) const override;

    public:
        void setOffset(const Vector2D & offset);

    private:
        Vector2D * offset;

    private:
        bool value;

    private:
        int lastIndexTriangle;
};
