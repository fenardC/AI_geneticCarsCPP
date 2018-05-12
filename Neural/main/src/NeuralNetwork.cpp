#include "Neural/main/inc/NeuralNetwork.hpp"

#include <sstream>

#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralInputValue.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"


NeuralNetwork::NeuralNetwork()
    : NeuralNetwork(1) {
    /* Add more if needed. */
}

NeuralNetwork::NeuralNetwork(double maxValue)
    : listInput()
    , listLayer()
    , maxValue(maxValue) {
}

NeuralNetwork::~NeuralNetwork() {
    {
        auto deleteInput = [](const NeuralInput * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~NeuralNetwork(): neural input: " + address.str());

            delete p;
        };
        std::for_each(listInput.begin(), listInput.end(), deleteInput);
        listInput.clear();
    }
    {
        auto deleteLayer = [](const NeuralLayer * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::debug("~NeuralNetwork(): neural layer: " + address.str());
            delete p;
        };
        std::for_each(listLayer.begin(), listLayer.end(), deleteLayer);
        listLayer.clear();
    }
}

void NeuralNetwork::initFromDna(GeneticDnaNeuralNetwork & dna) {
    std::vector<GeneticGene *> listGene = dna.getListGene();
    int i = 0;

    for (NeuralLayer * layer : listLayer) {
        for (NeuralNeuron * neuron : layer->getListNeuron()) {
            neuron->getListWeight().clear();

            for (size_t j = 0; j < neuron->getListInput().size(); j++) {
                GeneticGene * gene = listGene[i];
                const CDouble * const weight = static_cast<CDouble *>(gene->getValue()[0]);
                neuron->getListWeight().push_back(new CDouble(weight->doubleValue()));
                i++;
            }

            GeneticGene * gene = listGene[i];
            const CDouble * const weight = static_cast<CDouble *>(gene->getValue()[0]);
            neuron->setThreshold(weight->doubleValue() * neuron->getListWeight().size());
            i++;
        }
    }
}

GeneticDnaNeuralNetwork * NeuralNetwork::generateDnaModel() {
    int nb = 0;

    for (NeuralLayer * layer : listLayer) {
        for (NeuralNeuron * neuron : layer->getListNeuron()) {
            nb += neuron->getListInput().size() + 1;
        }
    }

    //Logger.debug(CLASS_NAME + "generateDnaModel() " + "DNA Length = " + nb);

    return new GeneticDnaNeuralNetwork(-maxValue, maxValue, 1, nb);
}

void NeuralNetwork::render(Drawer & d, double x, double y, DrawParameterNeuralNetwork param) const {
    int radius = param.getRatioNeuron() * 5;
    int offsetX = param.getRatioX() * 25;
    int offsetY = param.getRatioY() * 16;

    for (size_t i = 0; i < listLayer.size(); i++) {
        NeuralLayer * layer = listLayer[i];

        for (size_t j = 0; j < layer->getListNeuron().size(); j++) {
            const NeuralNeuron * const neuron = layer->getListNeuron()[j];

            double posX = x + offsetX * (i - listLayer.size() / 2.0);
            double posY = y + offsetY * (j - layer->getListNeuron().size() / 2.0);

            d.setColor(Misc::mix(DrawParameterNeuralNetwork::getColorDesactivated(),
                                 DrawParameterNeuralNetwork::getColorActivated(),
                                 neuron->getOutput()));

            d.fillCircle(posX, posY, radius);
        }
    }

    for (size_t i = 1; i < listLayer.size(); i++) {
        NeuralLayer * layer = listLayer[i];

        for (size_t j = 0; j < layer->getListNeuron().size(); j++) {
            NeuralNeuron * const neuron = layer->getListNeuron()[j];

            double posX = x + offsetX * (i - listLayer.size() / 2.0);
            double posY = y + offsetY * (j - layer->getListNeuron().size() / 2.0);

            for (NeuralInput * input : neuron->getListInput()) {
                Logger::debug(std::string("NeuralNetwork::render()"));
                NeuralNeuron * neuron2 = dynamic_cast<NeuralNeuron *>(input);

                if (nullptr != neuron2) {
                    std::vector<NeuralNeuron *> neurons = listLayer[i - 1]->getListNeuron();

                    auto it = std::find(neurons.begin(), neurons.end(), neuron2);

                    if (it == neurons.end()) {
                        // neuron2 not in vector
                    }
                    else {
                        auto pos = std::distance(neurons.begin(), it);
                        double posX2 = x + offsetX * (i - 1 - listLayer.size() / 2.0);
                        double posY2 = y + offsetY * (pos - listLayer[i - 1]->getListNeuron().size() / 2.0);

                        Logger::debug(std::string("NeuralNetwork::render()"));
                        d.setColor(param.getColorLink());
                        d.drawLine(posX, posY, posX2, posY2);
                    }
                }
            }
        }
    }
}

void NeuralNetwork::random() {
    for (NeuralLayer * layer : listLayer) {
        layer->random(-maxValue, maxValue);
    }
}

void NeuralNetwork::calculate() {
    for (NeuralLayer * layer : listLayer) {
        layer->calculate();
    }
}

void NeuralNetwork::connectAllInputOnFirstLayer() {
    if (!listLayer.empty()) {
        for (NeuralNeuron * neuron : listLayer[0]->getListNeuron()) {
            for (NeuralInput * input : listInput) {
                neuron->addInput(input);
            }
        }
    }
}

void NeuralNetwork::addLayer(NeuralLayer * const layer) {
    listLayer.push_back(layer);
}

std::vector<NeuralLayer *> NeuralNetwork::getListLayer() const {
    return listLayer;
}

void NeuralNetwork::addInput(NeuralInput * const input) {
    listInput.push_back(input);
}

void NeuralNetwork::setInputValue(const int index, const double value) {
    static_cast<NeuralInputValue *>(listInput[index])->setValue(value);
}

std::vector<double> NeuralNetwork::getListResult() const {
    std::vector<double> listResult;

    NeuralLayer * layer = listLayer[listLayer.size() - 1];

    for (NeuralNeuron * neuron : layer->getListNeuron()) {
        listResult.push_back(neuron->getOutput());
    }

    return listResult;
}

std::vector<NeuralInput *> & NeuralNetwork::getListInput() {
    return listInput;
}
