#include "CObject/main/inc/CDouble.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Genetic/main/inc/GeneticPopulation.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralInputValue.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNetwork.hpp"
#include <memory>

static const double NETWORK_GENE_VALUE_MAX = 5.0;

static const int NETWORK_GENE_SIZE = 1;

static void testApp() {

    {
        Logger::info(std::string("-------------------------"));

        auto network = std::make_unique<NeuralNetwork>();

        network->addInput(std::make_shared<NeuralInputValue>());
        network->addInput(std::make_shared<NeuralInputValue>());
        network->addInput(std::make_shared<NeuralInputValue>());
        network->addInput(std::make_shared<NeuralInputValue>());

        /* 2 neurons x (3 inputs + threshold) */
        const auto dnaNetwork = std::make_unique<GeneticDnaNeuralNetwork>(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX,
                                NETWORK_GENE_SIZE, 2 * 5);

        const auto layerOuput = std::make_shared<NeuralLayer>(NeuralActivation::SIGMOID, 2);
        network->addLayer(layerOuput);
        network->connectAllInputOnFirstLayer();

        const double weights[5 * 2] = {
            1.0, 2.0, 3.0, 4.0, 5.0,
            1.1, 2.1, 3.1, 4.1, 5.1
        };
        const int weightsCount = sizeof(weights) / sizeof(weights[0]);

        for (int i = 0; i < weightsCount; i++) {
            GeneticGeneDouble * geneDouble = new GeneticGeneDouble(0, 5, 1);
            CDouble * weight = new CDouble(weights[i]);
            geneDouble->getCode().push_back(weight);
            dnaNetwork->getListGene().push_back(static_cast<GeneticGene *>(geneDouble));
        }

        Logger::info(std::string("dnaNetwork : After push_back(): ") + dnaNetwork->toString());

        Logger::info(std::string(""));
        GeneticIndividual * const indiv = new GeneticIndividual(dynamic_cast<GeneticDna *>(dnaNetwork.get()));
        Logger::info(std::string("indiv : After new: ") + indiv->toString());


        network->initFromDna(*static_cast<GeneticDnaNeuralNetwork *>(indiv->getDna()));

        /* Update network with line sensor values for inputs */
        for (int i = 0; i < 4; i++) {
            network->setInputValue(i, 2.0);
        }

        network->calculate();

        /* Get outputs from network. */
        const int engineCommand = Misc::mix(-128.0, 128.0, network->getListResult()[0]);
        const int wheelCommand = Misc::mix(-128.0, 128.0, network->getListResult()[1]);

        Logger::info(std::string("engineCommand : ") + std::to_string(engineCommand));
        Logger::info(std::string("wheelCommand  : ") + std::to_string(wheelCommand));

        dnaNetwork->destroy();
        indiv->destroy();
        delete indiv;
    }

    {
        Logger::info(std::string("-------------------------"));

        auto network = std::make_unique<NeuralNetwork>(NETWORK_GENE_VALUE_MAX);
        auto population = std::make_unique<GeneticPopulation>();

        network->addInput(std::make_shared<NeuralInputValue>());
        network->addInput(std::make_shared<NeuralInputValue>());

        const auto layerOuput = std::make_shared<NeuralLayer>(NeuralActivation::SIGMOID, 2);
        network->addLayer(layerOuput);
        network->connectAllInputOnFirstLayer();

        /* Initialize weight of neurons with random values. */
        population->generatePopulation(10, network->generateDnaModel()->randomDna());

        double score = 0;

        for (auto indiv : population->getListIndividual()) {
            indiv->setScore(score);
            score += 2;
            Logger::info(std::string("indiv : ") + indiv->toString());
        }

        Logger::info(std::string("-------------------------"));

        population->proceedNextGeneration();

        for (auto const indiv : population->getListIndividual()) {
            Logger::info(std::string("indiv : ") + indiv->toString());
        }
    }

    Logger::info(std::string("END"));
}

int main() {
    testApp();
    return 0;
}
