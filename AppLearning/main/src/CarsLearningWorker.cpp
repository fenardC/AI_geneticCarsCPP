#include "AppLearning/main/inc/CarsLearningWorker.hpp"
#include "AppLearning/main/inc/TrackData1.hpp"
#include "AppLearning/main/inc/TrackData2.hpp"
#include "AppLearning/main/inc/TrackData3.hpp"
#include "AppLearning/main/inc/TrackData4.hpp"
#include "AppLearning/main/inc/AppLearningUi.h"
#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Misc/main/inc/BezierSpline2D.hpp"
#include "Misc/main/inc/Vector2D.hpp"

CarsLearningWorker::Worker::Worker(CarsLearningWorker & parent)
    : ::QTimer()
    , onRunning(true)
    , lapCount(0)
    , parent(parent)
    , learningCount(0)
    , isOnSameTrack(false)
    , validCarAmount(0)
    , validCarTrackCompletionBest(0)
    , trackCompletionBest(0)
    , carScoreBest(0) {

    /* Connect ourself timer with paint event of ui. */
    QObject::connect(this, SIGNAL(timeout()), parent.mainUi, SLOT(update()));
}

CarsLearningWorker::Worker::~Worker() {
    QTimer::stop();
}

void CarsLearningWorker::Worker::run(Drawer & drawer) {
    if (onRunning) {
        doCarLearning(drawer);
    }
    else {
        drawer.clear();
        drawer.setColor(QColor(Qt::white));
        drawer.drawString("LEARNING APPLICATION FINISHED", 500, 500);
        drawer.show();
    }
}

void CarsLearningWorker::Worker::startRunning() {
    onRunning = true;
    QTimer::start(CarMotionHelper::WORKER_DELAY_IN_MS);
    Logger::trace(std::string("startRunning()<"));
}

void CarsLearningWorker::Worker::stopRunning() {
    onRunning = false;
    QTimer::stop();
    Logger::trace(std::string("Timer has just been stopped."));
}


void CarsLearningWorker::Worker::checkAndChangeTrack() {
    isOnSameTrack = false;
    parent.trackListIndex++;

    if (parent.trackListIndex > (parent.trackList.size() - 1)) {
        parent.trackListIndex = 0;
        learningCount++;
    }

    parent.currentTrack = parent.trackList[parent.trackListIndex];
    trackCompletionBest = 0;

    if (learningCount > 4) {
        stopRunning();
    }
}

void CarsLearningWorker::Worker::displayStatistics(Drawer & drawer) const {
    const int posX = 800;
    drawer.setColor(QColor(Qt::green));
    drawer.drawString(parent.currentTrack->getName() +
                      std::string(" (") + std::to_string(TRACK_SPLINE_WIDTH) + std::string(")") +
                      std::string("/") + std::to_string(CAR_MILLIS_PER_TICK) +
                      std::string("/") + std::to_string(WORKER_DELAY_IN_MS), posX, 20);
    drawer.drawString(std::string("LEARNING           : ") + std::to_string(learningCount), posX, 40);
    drawer.drawString(std::string("GENERATION      : ") + std::to_string(parent.population->getGenerationNumber()), posX, 60);
    drawer.drawString(std::string("NB CARS             : ") + std::to_string(validCarAmount), posX, 80);
    drawer.drawString(std::string("SCORE (BEST)    : ") + std::to_string(carScoreBest), posX, 100);
    drawer.drawString(std::string("PERCENT (BEST): ") + std::to_string(trackCompletionBest), posX, 120);
    drawer.drawString(std::string("PERCENT            : ") + std::to_string(validCarTrackCompletionBest), posX, 140);
}

void CarsLearningWorker::Worker::doCarLearning(Drawer & drawer) {
    /* Clear graphics of drawer. */
    drawer.clear();
    /* Some progress informations on screen*/
    displayStatistics(drawer);

    /* The track on screen. */
    displayTrackForCar(drawer, *parent.currentTrack);

    /* For debug. */
    parent.currentTrack->renderSplineDebug(drawer);

    isOnSameTrack = true;
    validCarAmount = 0;
    validCarTrackCompletionBest = 0;
    int validCarNoProgress = 0;

    for (Car * car : parent.carList) {
        if (isOnSameTrack && car->isOnTrack()) {
            /* Update car on track. */
            parent.moveCar(drawer, *car);

            /* Check if the car is actually moving. */
            const bool noProgress = isNoProgress(car->getEngine());

            if (noProgress) {
                validCarNoProgress++;
            }

            /* Display neurons */
            if (NEURAL_NETWORK_DRAW) {
                Vector2D * carPos = car->getPosition();
                DrawParameterNeuralNetwork * param = new DrawParameterNeuralNetwork();
                parent.getNetwork().render(drawer, carPos->getX(), carPos->getY(), *param);
                delete carPos;
                delete param;
            }

            double trackCompletion = car->getTrackPercentCompletion();

            if (trackCompletion < 3.0) {
                trackCompletion = 0;
            }

            double score = car->getIndiv()->getScore() + (noProgress ? 0 : trackCompletion);

            updateValidCarStatistics(trackCompletion, score);

            /* ========= AT END OF EACH RACE ================ */
            /* For each car set the score. */
            car->getIndiv()->setScore(score);

            if (score > carScoreBest) {
                car->setColor(QColor(Qt::red));
            }

            if (trackCompletion > 99.1) {
                car->getIndiv()->setScore(score + 2000);

                Logger::debug(std::string("GENERATION : ") + std::to_string(parent.population->getGenerationNumber()));
                Logger::debug(std::string("TRACK   ") + parent.currentTrack->getName());
                Logger::debug(std::string("CAR     ") + car->getName());
                Logger::debug(std::string("SCORE   ") + std::to_string(car->getIndiv()->getScore()));
                Logger::debug(std::string("PERCENT (BEST): ") + std::to_string(trackCompletionBest) + std::string("\n"));
                Logger::debug(std::string("PERCENT ") + std::to_string(trackCompletion) + std::string("\n"));
                Logger::debug(car->getIndiv()->toString());

                checkAndChangeTrack();
            }
        }
    }

    drawer.show();

    if (!isOnSameTrack || (validCarAmount == validCarNoProgress)) {
        /* Create new generation. */
        parent.population->proceedNextGeneration();
        Logger::debug(std::string("GENERATION : ") + std::to_string(parent.population->getGenerationNumber()));

        for (size_t index = 0, carListSize = parent.carList.size(); index < carListSize; index++) {
            Car * const car = parent.carList[index];
            car->setIndiv(parent.population->getListIndividual()[index]);
            startCarOnTrack(parent.currentTrack, *car);
        }
    }
}

bool CarsLearningWorker::Worker::isNoProgress(int carEngine) const {
    bool result = false;

    if ((-1 <= carEngine) && (carEngine <= 1)) {
        result = true;
    }

    return result;
}

void CarsLearningWorker::Worker::updateValidCarStatistics(double trackCompletion, double score) {

    validCarAmount++;

    if (trackCompletion > trackCompletionBest) {
        trackCompletionBest = trackCompletion;
    }

    if (trackCompletion > validCarTrackCompletionBest) {
        validCarTrackCompletionBest = trackCompletion;
    }

    if (score > carScoreBest) {
        carScoreBest = score;
    }
}

/*********************************************************************************/
const int CarsLearningWorker::CAR_POPULATION_SIZE = 200;
const bool CarsLearningWorker::NEURAL_NETWORK_DRAW = false;

CarsLearningWorker::CarsLearningWorker(const AppLearningUi * mainUi)
    : ::CarMotionHelper()
    , mainUi(mainUi)
    , trackList()
    , trackListIndex(0)
    , currentTrack(nullptr)
    , population(nullptr)
    , carList()
    , worker(*this) {

    /* Super class creates the neural network. */
    initNetwork();

    init();
}

CarsLearningWorker::~CarsLearningWorker() {
}

void CarsLearningWorker::doWork(Drawer & drawer) {
    worker.run(drawer);
}

void CarsLearningWorker::init() {
    /* Prepare track for the cars. */
    std::vector<TrackData *> trackDataList;

    trackDataList.push_back(new TrackData1());
    trackDataList.push_back(new TrackData2());
    trackDataList.push_back(new TrackData3());
    trackDataList.push_back(new TrackData4());

    for (TrackData * t : trackDataList) {
        /* For debug */
        t->debug();
        BezierSpline2D * spline = new BezierSpline2D(t->getPointsAndPerpList());

        trackList.push_back(new Track(t->getName(),
                                      spline, TRACK_SPLINE_WIDTH,
                                      spline->getListResultPoint().size() * 100 * CAR_MILLIS_PER_TICK));
#warning memory leak?
        //delete t;
    }

#warning memory leak?
    // trackDataList.clear();

    currentTrack = trackList[0];

    population = new GeneticPopulation();
    /* Initialize weight of neurons with random values. */
    population->generatePopulation(CAR_POPULATION_SIZE, getNetwork().generateDnaModel()->randomDna());

    /* ============ AT EACH BEGINING OF RACE ============ */
    /* Create the cars provided the genetic. */
    // Random colorMaker = new Random();
    int i = 0;

    for (std::shared_ptr<GeneticIndividual> indiv : population->getListIndividual()) {
        Car * car = new Car(std::string("Car_") + std::to_string(i++), CAR_SENSOR_TYPE, CAR_RATIO);
        QColor color;
        color.setRgb(static_cast<int>(Misc::random(0.0, 255.0)),
                     static_cast<int>(Misc::random(0.0, 255.0)),
                     static_cast<int>(Misc::random(0.0, 255.0)),
                     static_cast<int>(Misc::random(0.0, 255.0)));

        car->setColor(color);
        car->setIndiv(indiv);
        carList.push_back(car);
        startCarOnTrack(currentTrack, *car);
    }
}

void CarsLearningWorker::startRunning() {
    worker.startRunning();
}

void CarsLearningWorker::stopRunning() {
    worker.stopRunning();
}
