
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"


#include "Debug/main/inc/Logger.hpp"
#include "CObject/main/inc/CDouble.hpp"
#include "Misc/main/inc/Vector2D.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <ostream>

static const int SENSOR_LINE_NUMBER = 8;

static const int NETWORK_NUMBER_OF_NEURONS = 2;

static const double NETWORK_GENE_VALUE_MAX = 5.0;

static const int NETWORK_GENE_SIZE = 1;

static const int NETWORK_GENE_NUMBER = NETWORK_NUMBER_OF_NEURONS * (SENSOR_LINE_NUMBER + 1 + 1);

#define assertEquals( string, val, expected, delta ) \
        if((std::abs((val) - (expected))) > (delta)) { \
            std::cout << (string) << " " << (val) << " does not match " << (expected) << std::endl; \
        } \

/**
 * Rigourous Test :-)
 */
static void testApp() {
    const double delta = 1E-15;

    Misc::init();

    {
        GeneticGeneDouble * const geneDouble = new GeneticGeneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, 10);

        geneDouble->randomGene();
        Logger::debug(std::string("geneDouble : After randomGene(): ") + geneDouble->toString());

        geneDouble->destroy();
        Logger::debug(std::string("geneDouble : After destroy(): ") + geneDouble->toString());
        delete geneDouble;
    }

    {
        GeneticGeneDouble geneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, 20);

        Logger::debug(std::string(""));

        geneDouble.randomGene();
        Logger::debug("geneDouble: After randomGene(): " + geneDouble.toString());

        GeneticGene * geneDoubleClone = geneDouble.clone();
        Logger::debug("geneDoubleClone: After clone(): " + geneDoubleClone->toString());

        geneDouble.destroy();
        Logger::debug(std::string("geneDouble : After destroy(): ") + geneDouble.toString());

        geneDoubleClone->destroy();
        Logger::debug(std::string("geneDoubleClone : After destroy(): ") + geneDoubleClone->toString());
        delete geneDoubleClone;
    }

    {
        /*const*/ CDouble weights[NETWORK_GENE_NUMBER] = {
            1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
            11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0
        };

        Logger::debug(std::string(""));

        /* 2 neurons x (8 sensors lines + speed input + threshold) */
        GeneticDnaNeuralNetwork * const dnaNetwork =
            new GeneticDnaNeuralNetwork(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX,
                                        NETWORK_GENE_SIZE, NETWORK_GENE_NUMBER);

        Logger::debug(std::string("dnaNetwork: After new: ") + dnaNetwork->toString());

        for (int i = 0; i < NETWORK_GENE_NUMBER; i++) {
            GeneticGeneDouble * geneDouble = new GeneticGeneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, NETWORK_GENE_SIZE);

            Logger::debug(std::string("weights[") + std::to_string(i) + std::string("]: ")  + weights[i].toString());
            geneDouble->getCode().push_back(static_cast<CObject *>(&weights[i]));
            Logger::debug(std::string("geneDouble: After push_back(): ") + geneDouble->toString());

            CObject * code = geneDouble->getCode()[0];
            Logger::debug(std::string("geneDouble: After getCode(): ") + code->toString());

            dnaNetwork->getListGene().push_back(static_cast<GeneticGene *>(geneDouble));
            Logger::debug(std::string("dnaNetwork : After push_back(): ") + dnaNetwork->toString());
#warning to be finished
#if 0
            ObjectCpp value = dnaNetwork->getListGene()[i]->getValue()[0];
            Logger::debug(std::string("dnaNetwork: After getListGene() ->getValue(): ") + value.to_string()));
#endif
        }


        Logger::debug(std::string(""));
        GeneticDnaNeuralNetwork * const dnaNetworkClone = dnaNetwork->clone();
        Logger::debug("dnaNetworkClone: After clone(): " + dnaNetworkClone->toString());

        dnaNetwork->destroy();
        Logger::debug(std::string("dnaNetwork : After destroy(): ") + dnaNetwork->toString());
        delete dnaNetwork;

        GeneticIndividual * const indiv = new GeneticIndividual(dnaNetworkClone);
        Logger::debug(std::string("indiv : After new: ") + indiv->toString());



        indiv->destroy();
        Logger::debug(std::string("indiv : After destroy(): ") + indiv->toString());
        // delete indiv;
    }

}

int main() {
    testApp();
    return 0;
}
