
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"


GeneticGeneTreeBranch::GeneticGeneTreeBranch(std::vector<CObject *> & listPossible)
    : ::GeneticGeneObject(listPossible)
    , parent(nullptr) {
}

GeneticGeneTreeBranch::~GeneticGeneTreeBranch() {
}

GeneticGeneTreeBranch * GeneticGeneTreeBranch::clone() { /*const*/
    GeneticGeneTreeBranch * const geneTreeBranch = new GeneticGeneTreeBranch(listPossible);

    for (GeneticGeneTreeBranch * g : listBranch) {
        geneTreeBranch->listBranch.push_back(g);
    }

    geneTreeBranch->parent = parent;
    return geneTreeBranch;
}


int GeneticGeneTreeBranch::getLength() const {
    int i = 1;

    for (GeneticGeneTreeBranch * operand : listBranch) {
        i += operand->getLength();
    }

    return i;
}

std::vector<GeneticGeneTreeBranch *> GeneticGeneTreeBranch::getListGeneticGeneTreeBranch() {
    std::vector<GeneticGeneTreeBranch *> list;
    list.push_back(this);

#warning to be finished
#if 0

    for (GeneticGeneTreeBranch * operand : listBranch) {
        list.addAll(operand->getListGeneticGeneTreeBranch());
    }

#endif
    return list;
}

GeneticGeneTreeBranch * GeneticGeneTreeBranch::getParent() const {
    return parent;
}


void GeneticGeneTreeBranch::setParent(GeneticGeneTreeBranch * const parent) {
    this->parent = parent;
}


std::vector<GeneticGeneTreeBranch *> & GeneticGeneTreeBranch::getListBranch() {
    return listBranch;
}

void GeneticGeneTreeBranch::destroy() {
    for (GeneticGeneTreeBranch * gene : listBranch) {
        gene->destroy();
    }

    listBranch.clear();
    delete parent;
}
