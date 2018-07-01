#pragma once

#include "CoreApp/main/inc/CarMotionHelper.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Genetic/main/inc/GeneticPopulation.hpp"
#include "DemoMisc/main/inc/Car.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "TrackData/main/inc/TrackData.hpp"

#include <QTimer>
#include <QThread>
#include <QObject>

class AppLearningUi;

class CarsLearningWorker final : public CarMotionHelper {

    private:
        class Worker: public QTimer {
            public:
                Worker(CarsLearningWorker & parent);

            public:
                ~Worker();

            public:
                void run(Drawer & drawer);

            public:
                void startRunning();

            public:
                void stopRunning();

            private:
                void checkAndChangeTrack();

            private:
                void displayStatistics(Drawer & drawer) const;

            private:
                void doCarLearning(Drawer & drawer);

            private:
                bool isNoProgress(int carEngine) const;

            private:
                void updateValidCarStatistics(double trackCompletion, double score);

            private:
                volatile bool onRunning;

            private:
                int lapCount;

            private:
                CarsLearningWorker & parent;

            private:
                int learningCount;

            private:
                bool isOnSameTrack;

            private:
                int validCarAmount;

            private:
                double validCarTrackCompletionBest;

            private:
                double trackCompletionBest;

            private:
                double carScoreBest;
        };

        /*********************************************************************************/
    public:
        const AppLearningUi * mainUi;

    public:
        CarsLearningWorker(const AppLearningUi * mainUi);

    public:
        ~CarsLearningWorker();

    public:
        void doWork(Drawer & drawer);

    private:
        void init();

    public:
        void startRunning();

    public:
        void stopRunning();

    private:
        static const int CAR_POPULATION_SIZE;

    private:
        static const bool NEURAL_NETWORK_DRAW;

    private:
        std::vector<Track *> trackList;

    private:
        size_t trackListIndex;

    public:
        Track * currentTrack;

    private:
        GeneticPopulation * population;

    private:
        std::vector<Car *> carList;

    private:
        Worker worker;
};
