
#pragma once

#include "AppRace/main/inc/AppRaceUi.h"
#include "AppRace/main/inc/CarParameters.hpp"
#include "CoreApp/main/inc/CarMotionHelper.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"

#include "Misc/main/inc/BezierSpline2D.hpp"

#include "DemoMisc/main/inc/Car.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "TrackData/main/inc/TrackData.hpp"
#include "AppRace/main/inc/TrackDataRace.hpp"

#include <QTimer>
#include <QObject>

class AppRaceUi;

class CarRacingWorker final : public CarMotionHelper {

    private:
        class Worker: public QTimer {
            public:
                Worker(CarRacingWorker & parent);

            public:
                ~Worker();

            public:
                void run(Drawer & drawer);

            public:
                void startRunning();

            public:
                void stopRunning();

            private:
                void displayStatistics(Drawer & drawer) const;


            public:
                void doCarRacing(Drawer & drawer);

            private:
                volatile bool onRunning;

            private:
                int lapCount;

            private:
                CarRacingWorker & parent;

            private:
                double trackCompletion;
        };

        /*********************************************************************************/
    public:
        const AppRaceUi * mainUi;

    public:
        CarRacingWorker(const AppRaceUi * mainUi);

    public:
        ~CarRacingWorker();

    public:
        void doWork(Drawer & drawer);

    private:
        void init();

    public:
        void startRunning();

    public:
        void stopRunning();

    private:
        static const bool NEURAL_NETWORK_DRAW;

    public:
        Track * currentTrack;

    private:
        Car * car;

    private:
        Worker worker;
};
