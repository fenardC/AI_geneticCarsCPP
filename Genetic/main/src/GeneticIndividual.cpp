#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include <sstream>

GeneticIndividual::GeneticIndividual(GeneticDna * const dna)
    : bloodline(false)
    , dna(dna)
    , score(0)
    , tag(nullptr) {
    {
        std::ostringstream address;
        address << static_cast<void const *>(dna);
        Logger::trace("GeneticIndividual::GeneticIndividual(): dna: " + address.str());
    }
}

GeneticIndividual::GeneticIndividual(std::shared_ptr<GeneticIndividual> indiv)
    : bloodline(false)
    , dna(indiv->dna->clone())
    , score(indiv->score)
    , tag(indiv->tag) {
    {
        std::ostringstream address;
        address << static_cast<void const *>(indiv.get());
        Logger::trace("GeneticIndividual::GeneticIndividual(): indiv: " + address.str());
    }
}

GeneticIndividual::~GeneticIndividual() {
    /* It is not responsibility of this to delete the dna that was given at construction. */
    Logger::trace("GeneticIndividual::~GeneticIndividual()<");
}

void GeneticIndividual::destroy() {
    Logger::trace("GeneticIndividual::destroy()>");

    dna->destroy();
    //delete tag;
    Logger::trace("GeneticIndividual::destroy()<");
}

GeneticDna * GeneticIndividual::getDna() const {
    return dna;
}

double GeneticIndividual::getScore() const {
    return score;
}

CObject * GeneticIndividual::getTag() const {
    return tag;
}

bool GeneticIndividual::isBloodline() const {
    return bloodline;
}

void GeneticIndividual::setBloodline(const bool bloodline) {
    this->bloodline = bloodline;
}


void GeneticIndividual::setScore(const double score) {
    this->score = score;
}

void GeneticIndividual::setTag(CObject * const tag) {
    this->tag = tag;
}

std::string GeneticIndividual::toString() const {
    std::stringstream result;

    if (nullptr != dna) {
        result << std::string("DNA : ");
        result << dna->toString();
        result << "\nScore : ";
        result << std::to_string(score);
    }

    return result.str();
}
