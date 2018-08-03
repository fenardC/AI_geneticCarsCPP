#include "AppRace/main/inc/CarRacingWorker.hpp"
#include "AppRace/main/inc/CarParameters.hpp"
#include "AppRace/main/inc/TrackDataRace.hpp"
#include "CoreApp/main/inc/CarMotionHelper.hpp"

#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "CObject/main/inc/CDouble.hpp"
#include "Misc/main/inc/BezierSpline2D.hpp"
#include "TrackData/main/inc/TrackData.hpp"
#include <memory>

CarRacingWorker::Worker::Worker(CarRacingWorker & parent)
    : ::QTimer()
    , onRunning(true)
    , lapCount(0)
    , parent(parent)
    , trackCompletion(0) {

    /* Connect ourself timer with paint event of ui. */
    QObject::connect(this, SIGNAL(timeout()), parent.mainUi, SLOT(update()));
}

CarRacingWorker::Worker::~Worker() {
    QTimer::stop();
}

void CarRacingWorker::Worker::run(Drawer & drawer) {
    if (onRunning) {
        doCarRacing(drawer);
    }
    else {
        drawer.clear();
        drawer.setColor(QColor(Qt::white));
        drawer.drawString("RACING APPLICATION FINISHED", 500, 500);
        drawer.show();
    }
}

void CarRacingWorker::Worker::startRunning() {
    onRunning = true;
    QTimer::start(CarMotionHelper::WORKER_DELAY_IN_MS);
    Logger::trace(std::string("CarRacingWorker::Worker::startRunning()<"));
}

void CarRacingWorker::Worker::stopRunning() {
    onRunning = false;
    QTimer::stop();
    Logger::debug(std::string("Timer has just been stopped."));
}

void CarRacingWorker::Worker::displayStatistics(Drawer & drawer) const {
    const int posX = 750;
    drawer.setColor(QColor(Qt::green));
    drawer.drawString(parent.currentTrack->getName() +
                      std::string(" (") + std::to_string(TRACK_SPLINE_WIDTH) + std::string(")") +
                      std::string("/") + std::to_string(CAR_MILLIS_PER_TICK) + std::string("/") +
                      std::to_string(WORKER_DELAY_IN_MS), posX, 30);
    drawer.drawString(std::string("PERCENT : ") + std::to_string(trackCompletion), posX, 50);
    drawer.drawString(std::string("LAPS       : ") + std::to_string(lapCount), posX, 70);
}

void CarRacingWorker::Worker::doCarRacing(Drawer & drawer) {

    Logger::trace(std::string("CarRacingWorker::Worker::doCarRacing()>"));

    /* Clear graphics of drawer. */
    drawer.clear();
    /* Some progress informations on screen*/
    displayStatistics(drawer);

    /* The track on screen. */
    displayTrackForCar(drawer, *parent.currentTrack);

    /* For debug. */
    parent.currentTrack->renderSplineDebug(drawer);

    /* Update car on track. */
    parent.moveCar(drawer, *parent.car);

    /* Display neurons */
    if (NEURAL_NETWORK_DRAW) {
        const int neuronPosX = 750;
        const int neuronPosY = 80;

        const DrawParameterNeuralNetwork param(4);
        parent.getNetwork().render(drawer, neuronPosX, neuronPosY, param);
    }

    trackCompletion = parent.car->getTrackPercentCompletion();
    lapCount = parent.car->getLap();
    drawer.show();
}

/*********************************************************************************/
const bool CarRacingWorker::NEURAL_NETWORK_DRAW = true;

CarRacingWorker::CarRacingWorker(const AppRaceUi * mainUi)
    : ::CarMotionHelper()
    , mainUi(mainUi)
    , currentTrack(nullptr)
    , car(nullptr)
    , worker(*this) {

    /* Super class creates the neural network. */
    initNetwork();

    init();
}

CarRacingWorker::~CarRacingWorker() {
    delete currentTrack;
    //car->getIndiv()->;
    //car->setIndiv(nullptr);
    delete car;
}

void CarRacingWorker::startRunning() {
    worker.startRunning();
}

void CarRacingWorker::stopRunning() {
    worker.stopRunning();
}

void CarRacingWorker::doWork(Drawer & drawer) {
    worker.run(drawer);
}

void CarRacingWorker::init() {
    /* Prepare track for the car. */
    const TrackDataRace * const trackDataRace = new TrackDataRace();
    /*const*/ BezierSpline2D * const spline = new BezierSpline2D(trackDataRace->getPointsAndPerpList());

    currentTrack = new Track(trackDataRace->getName(),
                             spline, TRACK_SPLINE_WIDTH,
                             spline->getListResultPoint().size() * 100 * CAR_MILLIS_PER_TICK);

    const CarParameters carParameters;
    const CarParameters::NetworkWeights * weights = carParameters.getNext();
    Logger::debug(std::string("CarRacingWorker::init()@ ") + weights->getName());

    /* 2 neurons x (8 sensors lines + speed input + threshold) */
    GeneticDnaNeuralNetwork * const dnaNetwork =
        new GeneticDnaNeuralNetwork(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX,
                                    NETWORK_GENE_SIZE, NETWORK_GENE_NUMBER);

    for (int i = 0; i < NETWORK_GENE_NUMBER; i++) {
        GeneticGeneDouble * const geneDouble =
            new GeneticGeneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX,
                                  NETWORK_GENE_SIZE);

        CDouble * weight = new CDouble(weights->getValue()[i]);
        geneDouble->getCode().push_back(weight);
        dnaNetwork->getListGene().push_back(static_cast<GeneticGene *>(geneDouble));
    }

    Logger::debug(std::string("CarRacingWorker::init()@ ") + dnaNetwork->toString());

    /* Initialize weight of neurons with values from learning. */
    std::shared_ptr<GeneticIndividual> indiv = std::make_shared<GeneticIndividual>(dnaNetwork->clone());

    /* ============ AT BEGINING OF RACE ============ */
    /* Create the car provided the genetic. */
    car = new Car("TheCar", CAR_SENSOR_TYPE, CAR_RATIO);
    car->setColor(QColor(Qt::red));
    car->setIndiv(indiv);
    startCarOnTrack(currentTrack, *car);
}

