#include "Debug/main/inc/Logger.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralInputValue.hpp"
#include "Neural/main/inc/NeuralNetwork.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"
#include <sstream>

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
    Logger::trace(std::string("NeuralNetwork::~NeuralNetwork()>"));

    listInput.clear();
    listLayer.clear();

    Logger::trace(std::string("NeuralNetwork::~NeuralNetwork()<"));
}

void NeuralNetwork::initFromDna(GeneticDnaNeuralNetwork & dna) {
    std::vector<GeneticGene *> listGene = dna.getListGene();
    int i = 0;

    for (auto layer : listLayer) {
        for (auto neuron : layer->getListNeuron()) {
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

    for (auto layer : listLayer) {
        for (auto neuron : layer->getListNeuron()) {
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
        auto layer = listLayer[i];

        for (size_t j = 0; j < layer->getListNeuron().size(); j++) {
            const auto neuron = layer->getListNeuron()[j];

            double posX = x + offsetX * (i - listLayer.size() / 2.0);
            double posY = y + offsetY * (j - layer->getListNeuron().size() / 2.0);

            d.setColor(Misc::mix(DrawParameterNeuralNetwork::getColorDesactivated(),
                                 DrawParameterNeuralNetwork::getColorActivated(),
                                 neuron->getOutput()));

            d.fillCircle(posX, posY, radius);
        }
    }

    for (size_t i = 1; i < listLayer.size(); i++) {
        auto layer = listLayer[i];

        for (size_t j = 0; j < layer->getListNeuron().size(); j++) {
            const auto neuron = layer->getListNeuron()[j];

            double posX = x + offsetX * (i - listLayer.size() / 2.0);
            double posY = y + offsetY * (j - layer->getListNeuron().size() / 2.0);

            for (auto input : neuron->getListInput()) {
                Logger::debug(std::string("NeuralNetwork::render()"));
                auto neuron2 = std::dynamic_pointer_cast<NeuralNeuron>(input);

                if (nullptr != neuron2) {
                    auto neurons = listLayer[i - 1]->getListNeuron();

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
    for (auto layer : listLayer) {
        layer->random(-maxValue, maxValue);
    }
}

void NeuralNetwork::calculate() {
    for (auto layer : listLayer) {
        layer->calculate();
    }
}

void NeuralNetwork::connectAllInputOnFirstLayer() {
    if (!listLayer.empty()) {
        for (auto neuron : listLayer[0]->getListNeuron()) {
            for (auto input : listInput) {
                neuron->addInput(input);
            }
        }
    }
}

void NeuralNetwork::addInput(std::shared_ptr<NeuralInput> const input) {
    listInput.push_back(input);
}

void NeuralNetwork::addLayer(std::shared_ptr<NeuralLayer> const layer) {
    listLayer.push_back(layer);
}

std::vector<std::shared_ptr<NeuralInput> > & NeuralNetwork::getListInput() {
    return listInput;
}

std::vector<std::shared_ptr<NeuralLayer> >NeuralNetwork::getListLayer() const {
    return listLayer;
}

std::vector<double> NeuralNetwork::getListResult() const {
    std::vector<double> listResult;

    auto layer = listLayer[listLayer.size() - 1];

    for (auto neuron : layer->getListNeuron()) {
        listResult.push_back(neuron->getOutput());
    }

    return listResult;
}

void NeuralNetwork::setInputValue(const int index, const double value) {
    static_cast<NeuralInputValue *>(listInput[index].get())->setValue(value);
}
