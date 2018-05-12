#include "Genetic/main/inc/GeneticIndividual.hpp"

#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDna.hpp"
#include <sstream>

GeneticIndividual::GeneticIndividual(GeneticDna * const dna)
    : score(0)
    , bloodline(false)
    , dna(dna)
    , tag(nullptr) {
    {
        std::ostringstream address;
        address << static_cast<void const *>(dna);
        Logger::trace("GeneticIndividual::GeneticIndividual(): dna: " + address.str());
    }
}

GeneticIndividual::GeneticIndividual(std::shared_ptr<GeneticIndividual> const indiv)
    : score(indiv->score)
    , bloodline(false)
    , dna(indiv->dna->clone())
    , tag(indiv->tag) {
    {
        std::ostringstream address;
        address << static_cast<void const *>(indiv.get());
        Logger::trace("GeneticIndividual::GeneticIndividual(): indiv: " + address.str());
    }
}

GeneticIndividual::~GeneticIndividual() {

    {
        std::ostringstream address;
        address << static_cast<void const *>(dna);
        Logger::trace("GeneticIndividual::~GeneticIndividual(): dna: " + address.str());
#if 0
        delete dna;
#endif
    }
#if 0
    {
        std::ostringstream address;
        address << static_cast<void const *>(tag);
        Logger::trace("GeneticIndividual::~GeneticIndividual(): tag: " + address.str());
        delete tag;
    }
#endif
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
    result << std::string("DNA : ");
    result << dna->toString();
    result << "\nScore : ";
    result << std::to_string(score);
    return result.str();
}
