#include "Genetic/main/inc/GeneticCrossParameter.hpp"

GeneticCrossParameter::GeneticCrossParameter() {

}

double GeneticCrossParameter::getCrossRatio() {
    return CROSS_RATIO;
}

const double GeneticCrossParameter::CROSS_RATIO = 0.7;
