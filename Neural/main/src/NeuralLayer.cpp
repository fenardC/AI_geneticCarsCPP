#include "Debug/main/inc/Logger.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"
#include <sstream>

NeuralLayer::NeuralLayer()
    : listNeuron() {
    /* Add more if needed. */
}

NeuralLayer::NeuralLayer(int nb)
    : NeuralLayer() {
    for (int i = 0 ; i < nb ; i++) {
        addNeuron(std::make_shared<NeuralNeuron>());
    }
}

NeuralLayer::NeuralLayer(const NeuralActivation * activationFunction, int nb)
    : NeuralLayer() {
    for (int i = 0 ; i < nb ; i++) {
        addNeuron(std::make_shared<NeuralNeuron>(activationFunction));
    }
}

NeuralLayer::~NeuralLayer() {
    Logger::trace(std::string("NeuralLayer::~NeuralLayer()>"));

    listNeuron.clear();

    Logger::trace(std::string("NeuralLayer::~NeuralLayer()>"));
}

void NeuralLayer::addNeuron(std::shared_ptr<NeuralNeuron> neuron) {
    listNeuron.push_back(neuron);
}

void NeuralLayer::calculate() const {
    for (auto neuron : listNeuron) {
        neuron->calculate();
    }

    for (auto neuron : listNeuron) {
        neuron->setOutput(neuron->getNewOutput());
    }
}

void NeuralLayer::connectAll(NeuralLayer & previousLayer) {
    for (auto neuron : listNeuron) {
        for (auto neuron2 : previousLayer.getListNeuron()) {
            neuron->addInput(neuron2);
        }
    }
}

std::vector<std::shared_ptr<NeuralNeuron>> NeuralLayer::getListNeuron() {
    return listNeuron;
}

void NeuralLayer::random(double min, double max) {
    for (auto neuron : listNeuron) {
        neuron->random(min, max);
    }
}
