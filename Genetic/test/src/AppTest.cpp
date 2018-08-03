#include "CObject/main/inc/CDouble.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticGeneFormulaOperand.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <memory>

static const int SENSOR_LINE_NUMBER = 8;

static const int NETWORK_NUMBER_OF_NEURONS = 2;

static const double NETWORK_GENE_VALUE_MAX = 5.0;

static const int NETWORK_GENE_SIZE = 1;

static const int NETWORK_GENE_NUMBER = NETWORK_NUMBER_OF_NEURONS * (SENSOR_LINE_NUMBER + 1 + 1);

static void testApp() {

    {
        const auto geneDouble = std::make_unique<GeneticGeneDouble>(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, 10);
        CDouble four(4.0);
        const GeneticGeneDouble * other = reinterpret_cast<GeneticGeneDouble *>(&four);
        CDouble::assertEquals(std::string("GeneticGeneDouble::equals()"),
                              geneDouble->equals(*other) ? CDouble(1.0) : CDouble(0.0), CDouble(1.0));
    }

    {
        auto geneFormulaOperand = std::make_unique<GeneticGeneFormulaOperand>();
        CInteger result = geneFormulaOperand->getNbOperandForOperator(CString(std::string("+")));
        Logger::info(std::string("geneFormulaOperand : After getNbOperandForOperator(): ") + result.toString());

        geneFormulaOperand->addOperator(std::string("dummy"), 1);

        geneFormulaOperand->randomGene();
    }
    {
        Logger::info(std::string("-------------------------"));
        GeneticGeneDouble * const geneDouble = new GeneticGeneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, 10);
        geneDouble->randomGene();
        Logger::info(std::string("geneDouble : After randomGene(): ") + geneDouble->toString());

        geneDouble->destroy();
        Logger::info(std::string("geneDouble : After destroy(): ") + geneDouble->toString());
        delete geneDouble;
    }

    {
        Logger::info(std::string("-------------------------"));
        GeneticGeneDouble geneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, 20);

        geneDouble.randomGene();
        Logger::info("geneDouble: After randomGene(): " + geneDouble.toString());

        GeneticGene * geneDoubleClone = geneDouble.clone();
        Logger::info("geneDoubleClone: After clone(): " + geneDoubleClone->toString());

        geneDouble.destroy();
        Logger::info(std::string("geneDouble : After destroy(): ") + geneDouble.toString());

        geneDoubleClone->destroy();
        Logger::info(std::string("geneDoubleClone : After destroy(): ") + geneDoubleClone->toString());
        delete geneDoubleClone;
    }

    {
        Logger::info(std::string("-------------------------"));
        /*const*/ CDouble weights[NETWORK_GENE_NUMBER] = {
            1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
            11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0
        };

        /* 2 neurons x (8 sensors lines + speed input + threshold) */
        GeneticDnaNeuralNetwork * const dnaNetwork =
            new GeneticDnaNeuralNetwork(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX,
                                        NETWORK_GENE_SIZE, NETWORK_GENE_NUMBER);

        Logger::info(std::string("dnaNetwork: After new: ") + dnaNetwork->toString());

        for (int i = 0; i < NETWORK_GENE_NUMBER; i++) {
            GeneticGeneDouble * geneDouble = new GeneticGeneDouble(-NETWORK_GENE_VALUE_MAX, NETWORK_GENE_VALUE_MAX, NETWORK_GENE_SIZE);

            Logger::info(std::string("weights[") + std::to_string(i) + std::string("]: ")  + weights[i].toString());
            /* Note that CDouble for weight is on heap. */
            geneDouble->getCode().push_back(static_cast<CObject *>(new CDouble(weights[i])));
            Logger::info(std::string("geneDouble: After push_back(): ") + geneDouble->toString());

            CObject * code = geneDouble->getCode()[0];
            Logger::info(std::string("geneDouble: After getCode(): ") + code->toString());

            dnaNetwork->getListGene().push_back(static_cast<GeneticGene *>(geneDouble));
            Logger::info(std::string("dnaNetwork : After push_back(): ") + dnaNetwork->toString());

            CObject * value = dnaNetwork->getListGene()[i]->getValue()[0];
            Logger::info(std::string("dnaNetwork: After getListGene() ->getValue(): ") + value->toString());
        }


        Logger::info(std::string(""));
        auto dnaNetworkClone = std::make_unique<GeneticDnaNeuralNetwork>(0.0, 0.0, 0, 0);
        dnaNetworkClone.reset(dnaNetwork->clone());
        Logger::info("dnaNetworkClone: After clone(): " + dnaNetworkClone->toString());

        dnaNetwork->destroy();
        Logger::info(std::string("dnaNetwork : After destroy(): ") + dnaNetwork->toString());
        delete dnaNetwork;

        GeneticIndividual * const indiv = new GeneticIndividual(dnaNetworkClone.get());
        Logger::info(std::string("indiv : After new: ") + indiv->toString());

        indiv->destroy();
        Logger::info(std::string("indiv : After destroy(): ") + indiv->toString());

        delete indiv;

        dnaNetworkClone->destroy();
    }

    Logger::info(std::string("END"));
}

int main() {
    testApp();
    return 0;
}
