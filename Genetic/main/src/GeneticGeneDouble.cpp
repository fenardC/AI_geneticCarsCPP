#include "CObject/main/inc/CDouble.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"
#include "Genetic/main/inc/GeneticDnaTree.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <sstream>
#include <vector>

GeneticGeneDouble::GeneticGeneDouble(double min, double max)
    : code()
    , max(max)
    , min(min)
    , size(1) {
}

GeneticGeneDouble::GeneticGeneDouble(double min, double max, int size)
    : code()
    , max(max)
    , min(min)
    , size(size) {
}

GeneticGeneDouble::~GeneticGeneDouble() {
    std::ostringstream address;
    address << static_cast<void const *>(this);
    Logger::trace("GeneticGeneDouble::~GeneticGeneDouble(): " + address.str());

    destroy();

    Logger::trace("GeneticGeneDouble::~GeneticGeneDouble()<");
}

GeneticGene * GeneticGeneDouble::clone() {
    GeneticGeneDouble * geneDouble = new GeneticGeneDouble(min, max, size);

    for (CObject * c : code) {
        geneDouble->code.push_back(c->clone());
    }

    return geneDouble;
}

void GeneticGeneDouble::destroy() {
    Logger::trace("GeneticGeneDouble::destroy()>");

    auto deleteObject = [](CObject * p) {
        std::ostringstream address;
        address << static_cast<void const *>(p);
        Logger::debug("GeneticGeneDouble()::destroy(): objects: " + address.str());
        delete p;
    };
    std::for_each(code.begin(), code.end(), deleteObject);
    code.clear();

    Logger::trace("GeneticGeneDouble::destroy()<");
}

bool GeneticGeneDouble::equals(const GeneticGene & other) const {
    bool result = false;

    try {
        const GeneticGeneDouble & myOther = const_cast<GeneticGeneDouble &>(dynamic_cast<const GeneticGeneDouble & >(other));
        const size_t size = code.size();
        const size_t myOtherSize = myOther.code.size();

        if (size == myOtherSize) {
            result = true;

            for (size_t i = 0; i < size; i++) {
                if (!code[i]->equals(*myOther.code[i])) {
                    result = false;
                    break;
                }
            }

        }
    }
    catch (const std::bad_cast & e) {
        Logger::error(std::string("GeneticGeneDouble::equals(): ") + std::string(e.what()));
    }

    return result;
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
    /* Delete previous codes if any. */
    destroy();

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
