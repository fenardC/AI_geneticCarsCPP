#include "Neural/main/inc/NeuralNeuron.hpp"

#include "Debug/main/inc/Logger.hpp"
#include "Neural/main/inc/NeuralInput.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <sstream>
#include <vector>



NeuralNeuron::NeuralNeuron()
    : NeuralNeuron(NeuralActivation::SIGMOID) {
    /* Add more if needed. */
}

NeuralNeuron::NeuralNeuron(const NeuralActivation * activationFunction)
    : activationFunction(activationFunction)
    , listInput()
    , listWeight()
    , newOutput(0.0)
    , output(0.0)
    , threshold(0.0) {
}

NeuralNeuron::~NeuralNeuron() {
    {
        auto deleteWeight = [](const CDouble * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~NeuralNeuron(): list weight: " + address.str());
            delete p;
        };
        std::for_each(listWeight.begin(), listWeight.end(), deleteWeight);
        listWeight.clear();
    }
    {
        /* Let to Network parent ownership for deleting inputs of neurons. */
        /* Note that an input can be shared with several neurons. */
#if 0
        auto deleteInput = [](const NeuralInput * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~NeuralNeuron(): list input: " + address.str());
            delete p;
        };
        std::for_each(listInput.begin(), listInput.end(), deleteInput);
#endif
        listInput.clear();
    }
}

void NeuralNeuron::addInput(std::shared_ptr<NeuralInput> const input) {
    listInput.push_back(input);
}

void NeuralNeuron::calculate() {
    const size_t listInputSize(listInput.size());

    if (listInputSize == listWeight.size() && activationFunction != nullptr) {
        double res = -threshold;

        for (size_t i = 0; i < listInputSize; i++) {
            res += listInput[i]->getValue() * listWeight[i]->doubleValue();
        }

        newOutput = activationFunction->calculate(res);
    }
}

std::vector<std::shared_ptr<NeuralInput>> & NeuralNeuron::getListInput() {
    return listInput;
}

std::vector<CDouble *> & NeuralNeuron::getListWeight() {
    return listWeight;
}

double NeuralNeuron::getNewOutput() const {
    return newOutput;
}

double NeuralNeuron::getOutput() const {
    return output;
}

double NeuralNeuron::getValue() const {
    return output;
}

void NeuralNeuron::random(double min, double max) {
    listWeight.clear();

    for (size_t i = 0; i < listInput.size(); i++) {
        listWeight.push_back(new CDouble(Misc::random(min, max)));
    }

    threshold = Misc::random(min, max);
}

void NeuralNeuron::setActivationFunction(const NeuralActivation * activationFunction) {
    this->activationFunction = activationFunction;
}

void NeuralNeuron::setOutput(double output) {
    this->output = output;
}

void NeuralNeuron::setThreshold(double threshold) {
    this->threshold = threshold;
}
