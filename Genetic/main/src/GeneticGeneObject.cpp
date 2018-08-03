#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneObject.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <sstream>

GeneticGeneObject::GeneticGeneObject(std::vector<CObject *> & listPossible)
    : code()
    , listPossible(listPossible)
    , size(1) {
}

GeneticGeneObject::GeneticGeneObject(std::vector<CObject *> & listPossible, int size)
    : code()
    , listPossible(listPossible)
    , size(size) {
}

GeneticGeneObject::~GeneticGeneObject() {
}

GeneticGene * GeneticGeneObject::clone() {
    GeneticGeneObject * geneObject = new GeneticGeneObject(listPossible, size);

    for (CObject * o : code) {
        geneObject->code.push_back(o);
    }

    return geneObject;
}

void GeneticGeneObject::destroy() {
    code.clear();
    listPossible.clear();
    Logger::trace("GeneticGeneObject::destroy()<");
}

bool GeneticGeneObject::equals(const GeneticGene & other) const {
    bool result = false;

    try {
        const GeneticGeneObject & myOther = const_cast<GeneticGeneObject &>(dynamic_cast<const GeneticGeneObject &>(other));
        const size_t size = code.size();
        const size_t myOtherSize = myOther.code.size();

        if (size == myOtherSize) {
            result = true;

            for (size_t i = 0; i < size; i++) {
                if (code[i] != (myOther.code[i])) {
                    result = false;
                    break;
                }
            }
        }
    }
    catch (const std::bad_cast & e) {
        Logger::error(std::string("GeneticGeneObject::equals(): ") + std::string(e.what()));
    }

    return result;
}


std::vector<CObject *> & GeneticGeneObject::getCode() {
    return code;
}

std::vector<CObject *> GeneticGeneObject::getListPossible() {
    return listPossible;
}

std::vector<CObject *> & GeneticGeneObject::getValue() {
    return code;
}

void GeneticGeneObject::mutate() {
    int i = 0;
    std::vector<CObject *> oldCode(code);

    while (i < 30 && std::equal(oldCode.begin(), oldCode.end(), code.begin())) {
        randomGene();
        i++;
    }
}

GeneticGeneObject * GeneticGeneObject::randomGene() {
    code.clear();

    if (!getListPossible().empty()) {
        for (int i = 0 ; i < size ; i++) {
            code.push_back(getListPossible()[Misc::random(0, getListPossible().size() - 1)]);
        }
    }

    return this;
}

void GeneticGeneObject::setListPossible(std::vector<CObject *> & listPossible) {
    this->listPossible = listPossible;
}

std::string GeneticGeneObject::toString() const {
    std::stringstream result;

    for (size_t i = 0 ; i < code.size() ; i++) {
        if (i > 0) {
            result << ", ";
        }

        result << code[i]->toString();
    }

    return result.str();
}
