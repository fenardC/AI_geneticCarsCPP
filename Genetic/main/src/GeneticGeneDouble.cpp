
#include <sstream>
#include <vector>

#include "CObject/main/inc/CDouble.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticDnaTree.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "Misc/main/inc/Misc.hpp"

GeneticGeneDouble::GeneticGeneDouble(double min, double max)
    : ::GeneticGeneDouble(min, max, 1) {
}

GeneticGeneDouble::GeneticGeneDouble(double min, double max, int size)
    : code()
    , size(size)
    , min(min)
    , max(max) {
}

GeneticGeneDouble::~GeneticGeneDouble() {
    destroy();
}

GeneticGene * GeneticGeneDouble::clone() {
    GeneticGeneDouble * geneDouble = new GeneticGeneDouble(min, max, size);

    for (CObject * c : code) {
        geneDouble->code.push_back(c->clone());
    }

    return geneDouble;
}

void GeneticGeneDouble::destroy() {
    Logger::debug("GeneticGeneDouble::destroy()>");

    auto deleteObject = [](CObject * p) {
        std::ostringstream address;
        address << static_cast<void const *>(p);
        Logger::debug("GeneticGeneDouble()::destroy(): objects: " + address.str());
        delete p;
    };
    //std::for_each(code.begin(), code.end(), deleteObject);
#warning to be done
    code.clear();
    Logger::debug("GeneticGeneDouble::destroy()<");
}

bool GeneticGeneDouble::equals(const GeneticGene & other) const {
    const GeneticGeneDouble  & myOther = const_cast<GeneticGeneDouble &>(dynamic_cast<const GeneticGeneDouble & >(other));
    const size_t size = code.size();
    const size_t myOtherSize = myOther.code.size();

    if (size == myOtherSize) {
        for (size_t i = 0; i < size; i++) {
            if (code[i] != (myOther.code[i])) {
                return false;
            }
        }

        return true;
    }

    return false;
}

std::vector<CObject *> & GeneticGeneDouble::getCode() {
    return code;
}

std::vector<CObject *> & GeneticGeneDouble::getValue() {
    return code;
}

void GeneticGeneDouble::mutate() {
    int i = 0;
    std::vector<CObject *> oldCode(code);

    while (i < 30 && std::equal(oldCode.begin(), oldCode.end(), code.begin())) {
        randomGene();
        i++;
    }
}

GeneticGeneDouble * GeneticGeneDouble::randomGene() {
    code.clear();

    for (int i = 0 ; i < size ; i++) {
        CDouble * random = new CDouble(Misc::random(min, max));
        code.push_back(static_cast<CObject *>(random));
    }

    return this;
}

std::string GeneticGeneDouble::toString() const {
    std::stringstream result;

    for (size_t i = 0 ; i < code.size() ; i++) {
        if (i > 0) {
            result << ", ";
        }

        result << code[i]->toString();
    }

    return result.str();
}
