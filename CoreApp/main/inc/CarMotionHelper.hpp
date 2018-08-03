
#pragma once
#include "DemoMisc/main/inc/Car.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Neural/main/inc/NeuralNetwork.hpp"

class CarMotionHelper {
    public:
        CarMotionHelper();

    public:
        ~CarMotionHelper();

    protected:
        NeuralNetwork & getNetwork();

    protected:
        void initNetwork() ;

    protected:
        void moveCar(Drawer & drawer, Car & car);

    protected:
        static void displayTrackForCar(Drawer & drawer, const Track & track);

    protected:
        static void startCarOnTrack(Track * const track, Car & car);

    protected:
        static const int CAR_MILLIS_PER_TICK;

    protected:
        static const double CAR_RATIO;

    protected:
        static const int CAR_SENSOR_TYPE;

    protected:
        static const int WORKER_DELAY_IN_MS;

    private:
        static const int NETWORK_ENGINE_INPUT_INDEX;

    private:
        static const int NETWORK_NUMBER_OF_NEURONS;

    protected:
        static const double NETWORK_GENE_VALUE_MAX;

    protected:
        static const int NETWORK_GENE_SIZE;

    protected:
        static const int NETWORK_GENE_NUMBER;

    protected:
        static const int TRACK_SPLINE_WIDTH;

    private:
        NeuralNetwork network;
};
