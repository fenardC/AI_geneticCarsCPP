#pragma once

#include <string>

#include "Draw/main/inc/Drawer.hpp"

class Car;

class CarSensor {

    public:
        CarSensor()
            : car(nullptr) {
        }

    public:
        virtual ~CarSensor() {
        }

    public:
        virtual void check() {
        }

    public:
        virtual double getValue() const = 0;

    public:
        virtual void render(Drawer & drawer) const {
            (void)(drawer);
        }

    public:
        void setCar(Car * const car) {
            this->car = car;
        }

    public:
        virtual void tick() {
            check();
        }

    protected:
        Car * car;
};
