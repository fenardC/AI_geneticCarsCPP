

#include "Debug/main/inc/Logger.hpp"
#include "CObject/main/inc/CDouble.hpp"
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Genetic/main/inc/GeneticPopulation.hpp"
#include "Misc/main/inc/Vector2D.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralInputValue.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNetwork.hpp"

#include <memory>
#include <ostream>
#include <string>


#define assertEquals( string, val, expected, delta ) \
        if((std::abs((val) - (expected))) > (delta)) { \
            std::cout << (string) << " " << (val) << " does not match " << (expected) << std::endl; \
        } \

static void testApp() {
    const double delta = 1E-15;

    Misc::init();
    {
        Logger::debug(std::string("-------------------------"));

        NeuralNetwork * network = new NeuralNetwork();

        network->addInput(new NeuralInputValue());
        network->addInput(new NeuralInputValue());
        network->addInput(new NeuralInputValue());
        network->addInput(new NeuralInputValue());

        /* 2 neurons x (3 inputs + threshold) */
        GeneticDnaNeuralNetwork * const dnaNetwork = new GeneticDnaNeuralNetwork(0.0, 5.0, 1, 2 * 5);

        NeuralLayer * const layerOuput = new NeuralLayer(NeuralActivation::SIGMOID, 2);
        network->addLayer(layerOuput);
        network->connectAllInputOnFirstLayer();

        const double weights[5 * 2] = {
            1.0, 2.0, 3.0, 4.0, 5.0,
            1.0, 2.0, 3.0, 4.0, 5.0
        };

        for (int i = 0; i < 2 * 5; i++) {
            GeneticGeneDouble * geneDouble = new GeneticGeneDouble(0, 5, 1);
            CDouble * weight = new CDouble(weights[i]);
            geneDouble->getCode().push_back(weight);
            dnaNetwork->getListGene().push_back(static_cast<GeneticGene *>(geneDouble));
        }

        Logger::debug(std::string("dnaNetwork : After push_back(): ") + dnaNetwork->toString());

        Logger::debug(std::string(""));
        GeneticIndividual * const indiv = new GeneticIndividual(dnaNetwork);
        Logger::debug(std::string("indiv : After new: ") + indiv->toString());


        network->initFromDna(*static_cast<GeneticDnaNeuralNetwork *>(indiv->getDna()));

        /* Update network with line sensor values for inputs */
        for (int i = 0; i < 4; i++) {
            network->setInputValue(i, double(2));
        }

        network->calculate();

        /* Get outputs from network. */
        const int engineCommand = Misc::mix(-128.0, 128.0, network->getListResult()[0]);
        const int wheelCommand = Misc::mix(-128.0, 128.0, network->getListResult()[1]);

        Logger::debug(std::string("engineCommand : ") + std::to_string(engineCommand));
        Logger::debug(std::string("wheelCommand  : ") + std::to_string(wheelCommand));

        dnaNetwork->destroy();
        delete dnaNetwork;
#if 0
        indiv->destroy();
        delete indiv;

        delete network;
#endif
    }



    {
        Logger::debug(std::string("-------------------------"));

        NeuralNetwork * network = new NeuralNetwork(5.0);
        GeneticPopulation * population = new GeneticPopulation();

        network->addInput(new NeuralInputValue());
        network->addInput(new NeuralInputValue());

        NeuralLayer * const layerOuput = new NeuralLayer(NeuralActivation::SIGMOID, 2);
        network->addLayer(layerOuput);
        network->connectAllInputOnFirstLayer();

        /* Initialize weight of neurons with random values. */
        population->generatePopulation(10, network->generateDnaModel()->randomDna());

        double score = 0;

        for (auto indiv : population->getListIndividual()) {
            indiv->setScore(score);
            score += 2;
            Logger::debug(std::string("indiv : ") + indiv->toString());
        }

        Logger::debug(std::string("-------------------------"));

        population->proceedNextGeneration();

        for (auto indiv : population->getListIndividual()) {
            Logger::debug(std::string("indiv : ") + indiv->toString());
        }
    }

    Logger::debug(std::string("END"));
}

int main() {
    testApp();
    return 0;
}
