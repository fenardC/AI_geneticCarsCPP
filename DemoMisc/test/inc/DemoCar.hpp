#pragma once

#include "DemoMisc/main/inc/Car.hpp"
#include "Draw/main/inc/Drawer.hpp"

class DemoCar {
    public:
        static const double CAR_MILLIS_PER_TICK;

    public:
        DemoCar();

    public:
        ~DemoCar();

        //private:
    public:
        void moveCar(Drawer & drawer);

    public:
        int getCommand() const {
            return command;
        }

    private:
        void initialize();

    private:
        Car * car;

    private:
        static const double CAR_RATIO;

    private:
        static const int CAR_SENSOR_TYPE;

    private:
        static const int TASK_PERFORMER_DELAY_IN_MS;

    private:
        int command;
};
