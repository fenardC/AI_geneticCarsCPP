
#include "Genetic/main/inc/GeneticGeneObject.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <sstream>

GeneticGeneObject::GeneticGeneObject(std::vector<CObject *> & listPossible)
    : listPossible(listPossible)
    , code()
    , size(1) {
}

GeneticGeneObject::GeneticGeneObject(std::vector<CObject *> & listPossible, int size)
    : listPossible(listPossible)
    , code()
    , size(size) {
}

GeneticGeneObject::~GeneticGeneObject() {
}

GeneticGene * GeneticGeneObject::clone() {
    GeneticGeneObject * geneObject = new GeneticGeneObject(listPossible, size);

    for (CObject * d : code) {
        geneObject->code.push_back(d);
    }

    return geneObject;
}

void GeneticGeneObject::destroy() {
    listPossible.clear();
    code.clear();
}

bool GeneticGeneObject::equals(const GeneticGene & other) const {
    const GeneticGeneObject & myOther = const_cast<GeneticGeneObject &>(dynamic_cast<const GeneticGeneObject &>(other));

#warning to be finished
#if 0

    if (getCode().size() == myOther.getCode().size()) {
        for (size_t i = 0; i < getCode().size(); i++) {
            if (getCode()[i] != (myOther.getCode()[i])) {
                return false;
            }
        }

        return true;
    }

#endif
    return false;
}


std::vector<CObject *> & GeneticGeneObject::getCode() {
    return code;
}

std::vector<CObject *> & GeneticGeneObject::getValue() {
    return code;
}

std::vector<CObject *> GeneticGeneObject::getListPossible() {
    return listPossible;
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
    std::stringstream stringStream;

    for (size_t i = 0 ; i < code.size() ; i++) {
        if (i > 0) {
            stringStream << ", ";
        }

        stringStream << code[i];
    }

    return stringStream.str();
}
