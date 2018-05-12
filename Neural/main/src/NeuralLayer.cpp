#include "Neural/main/inc/NeuralLayer.hpp"
#include <sstream>

#include "Debug/main/inc/Logger.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"


NeuralLayer::NeuralLayer()
    : listNeuron() {
    /* Add more if needed. */
}

NeuralLayer::NeuralLayer(int nb)
    : NeuralLayer() {
    for (int i = 0 ; i < nb ; i++) {
        addNeuron(new NeuralNeuron());
    }
}

NeuralLayer::NeuralLayer(const NeuralActivation * activationFunction, int nb)
    : NeuralLayer() {
    for (int i = 0 ; i < nb ; i++) {
        addNeuron(new NeuralNeuron(activationFunction));
    }
}

NeuralLayer::~NeuralLayer() {
    {
        auto deleteNeuron = [](const NeuralNeuron * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~NeuralLayer(): list neuron: " + address.str());

            delete p;
        };

        std::for_each(listNeuron.begin(), listNeuron.end(), deleteNeuron);
        listNeuron.clear();
    }
}

void NeuralLayer::addNeuron(NeuralNeuron * neuron) {
    listNeuron.push_back(neuron);
}

void NeuralLayer::calculate() const {
    for (NeuralNeuron * neuron : listNeuron) {
        neuron->calculate();
    }

    for (NeuralNeuron * neuron : listNeuron) {
        neuron->setOutput(neuron->getNewOutput());
    }
}

void NeuralLayer::connectAll(NeuralLayer & previousLayer) {
    for (NeuralNeuron * neuron : listNeuron) {
        for (NeuralNeuron * neuron2 : previousLayer.getListNeuron()) {
            neuron->addInput(neuron2);
        }
    }
}

std::vector<NeuralNeuron *> NeuralLayer::getListNeuron() {
    return listNeuron;
}

void NeuralLayer::random(double min, double max) {
    for (NeuralNeuron * neuron : listNeuron) {
        neuron->random(min, max);
    }
}
