
#include "Genetic/main/inc/GeneticCrossParameter.hpp"

const double GeneticCrossParameter::CROSS_RATIO = 0.7;

GeneticCrossParameter::GeneticCrossParameter() {

}

double GeneticCrossParameter::getCrossRatio() {
    return CROSS_RATIO;
}
