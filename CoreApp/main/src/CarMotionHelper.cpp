#include "CoreApp/main/inc/CarMotionHelper.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "DemoGui/main/inc/ScreenGeneticCar.hpp"
#include "DemoMisc/main/inc/Car.hpp"
#include "DemoMisc/main/inc/Track.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/Texture.hpp"
#include "Draw/main/inc/TextureModifier.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralInputValue.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNetwork.hpp"
#include <map>
#include <vector>


CarMotionHelper::CarMotionHelper()
    : network(NETWORK_GENE_VALUE_MAX) {
}

CarMotionHelper::~CarMotionHelper() {
}

NeuralNetwork & CarMotionHelper::getNetwork() {
    return network;
}

void CarMotionHelper::initNetwork() {
    /* Add entry for sensors. */
    for (int i = 0; i < ScreenGeneticCar::SENSOR_LINE_NUMBER; i++) {
        network.addInput(std::make_shared<NeuralInputValue>());
    }

    /* Add one more for speed. */
    network.addInput(std::make_shared<NeuralInputValue>());

    /* 2 neurons x (8 sensors lines + speed input + threshold) */
    auto layerOuput = std::make_shared<NeuralLayer>(NeuralActivation::SIGMOID, NETWORK_NUMBER_OF_NEURONS);
    network.addLayer(layerOuput);
    network.connectAllInputOnFirstLayer();
}

void CarMotionHelper::moveCar(Drawer & drawer, Car & car) {
    /* ========= AT EACH TICK OF COMPUTATION ========= */
    /* Load AI with DNA of this car. */
    network.initFromDna(*static_cast<GeneticDnaNeuralNetwork *>(car.getIndiv()->getDna()));

    /* Update network with line sensor values for inputs */
    for (int i = 0; i < ScreenGeneticCar::SENSOR_LINE_NUMBER; i++) {
        /* Sensors. */
        network.setInputValue(i, car.getSensorValue(std::string("s") + std::to_string(i)));
    }

    /* Update network with engine values for corresponding input */
    network.setInputValue(NETWORK_ENGINE_INPUT_INDEX, car.getEngine() / 128.0);

    /* Start computation of network. */
    network.calculate();

    /* Get outputs from network. */
    const int engineCommand = Misc::mix(-128.0, 128.0, network.getListResult()[0]);
    const int wheelCommand = Misc::mix(-128.0, 128.0, network.getListResult()[1]);

    /* Update Car with commands */
    car.setEngineCommand(engineCommand);
    car.setWheelCommand(wheelCommand);
    car.tick(CAR_MILLIS_PER_TICK);

    /* Display car. */
    car.render(drawer);
}

void CarMotionHelper::displayTrackForCar(Drawer & drawer, const Track & track) {
    track.renderDebug(drawer);
    track.renderCenterLine(drawer);
    track.renderStart(drawer);
}

void CarMotionHelper::startCarOnTrack(Track * const track, Car & car) {
    car.putOnTrack(track);
    car.setLap(0);
    car.setTimeLap(0);
    car.setBestIndexSpline(0);
    /* Give some speed and direction to the car */
    car.setEngineCommand(5);
    car.setWheelCommand(0);
    /* Update all internals of a car. */
    car.tick(0.01);
}

const int CarMotionHelper::CAR_MILLIS_PER_TICK = 18;

const double CarMotionHelper::CAR_RATIO = 0.5;

const int CarMotionHelper::CAR_SENSOR_TYPE = ScreenGeneticCar::TYPE_SENSOR_LINE;

const int CarMotionHelper::WORKER_DELAY_IN_MS = 10;

const int CarMotionHelper::NETWORK_ENGINE_INPUT_INDEX = ScreenGeneticCar::SENSOR_LINE_NUMBER;

const int CarMotionHelper::NETWORK_NUMBER_OF_NEURONS = 2;

const double CarMotionHelper::NETWORK_GENE_VALUE_MAX = 5.0;

const int CarMotionHelper::NETWORK_GENE_SIZE = 1;

const int CarMotionHelper::NETWORK_GENE_NUMBER =
    NETWORK_NUMBER_OF_NEURONS * (ScreenGeneticCar::SENSOR_LINE_NUMBER + 1 + 1);

/* 60 55 50:OK 48: KO 45:KO 42:KO 40:KO */
const int CarMotionHelper::TRACK_SPLINE_WIDTH = 60;

