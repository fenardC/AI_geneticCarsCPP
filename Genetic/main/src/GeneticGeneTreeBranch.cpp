#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"

GeneticGeneTreeBranch::GeneticGeneTreeBranch(std::vector<CObject *> & listPossible)
    : ::GeneticGeneObject(listPossible)
    , parent(nullptr) {
}

GeneticGeneTreeBranch::~GeneticGeneTreeBranch() {
    Logger::trace(std::string("GeneticGeneTreeBranch::~GeneticGeneTreeBranch()<"));
}

GeneticGeneTreeBranch * GeneticGeneTreeBranch::clone() { /*const*/
    GeneticGeneTreeBranch * const geneTreeBranch = new GeneticGeneTreeBranch(listPossible);

    for (auto b : listBranch) {
        geneTreeBranch->listBranch.push_back(b);
    }

    geneTreeBranch->parent = parent;
    return geneTreeBranch;
}

void GeneticGeneTreeBranch::destroy() {
    for (auto gene : listBranch) {
        gene->destroy();
    }

    listBranch.clear();
    delete parent;
    Logger::trace("GeneticGeneTreeBranch::destroy()<");
}

bool GeneticGeneTreeBranch::equals(const GeneticGene & /*other*/) const {
    Logger::error(std::string("GeneticGeneTreeBranch::equals(): returning false in all cases"));
    return false;
}

int GeneticGeneTreeBranch::getLength() const {
    int i = 1;

    for (auto operand : listBranch) {
        i += operand->getLength();
    }

    return i;
}

std::vector<GeneticGeneTreeBranch *> & GeneticGeneTreeBranch::getListBranch() {
    return listBranch;
}

std::vector<GeneticGeneTreeBranch *> GeneticGeneTreeBranch::getListGeneticGeneTreeBranch() {
    std::vector<GeneticGeneTreeBranch *> list;
    list.push_back(this);



    for (auto * operand : listBranch) {
#warning to be finished
#if 0
        list.addAll(operand->getListGeneticGeneTreeBranch());
#endif
    }

    return list;
}

GeneticGeneTreeBranch * GeneticGeneTreeBranch::getParent() const {
    return parent;
}


void GeneticGeneTreeBranch::setParent(GeneticGeneTreeBranch * const parent) {
    this->parent = parent;
}
