
#include <typeinfo>
#include <string>
#include <vector>

#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDnaTree.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "Misc/main/inc/Misc.hpp"

GeneticDnaTree::GeneticDnaTree()
    : listRoot() {

}

GeneticDnaTree::~GeneticDnaTree() {

}

GeneticDnaTree * GeneticDnaTree::clone() { /*const*/
    GeneticDnaTree * dnaTree = new GeneticDnaTree();

    for (GeneticGeneTreeBranch * const geneTreeBranch : listRoot) {
        dnaTree->getListRoot().push_back(geneTreeBranch->clone());
    }

    return dnaTree;
}

Couple<GeneticDna *, GeneticDna *> * GeneticDnaTree::cross(GeneticDna & other) {
    Logger::debug("GeneticDnaTree::cross()>");

    Couple<GeneticDna *, GeneticDna *> * couple(nullptr);

    try {
        GeneticDnaTree & b = dynamic_cast<GeneticDnaTree &>(other);

        GeneticDnaTree * dnaChildA = clone();
        GeneticDnaTree * dnaChildB = b.clone();

        int minRoot = std::min(dnaChildA->getListRoot().size(), dnaChildB->getListRoot().size());

        for (int i = 0; i < minRoot; i++) {

            std::vector<GeneticGeneTreeBranch *> codeA = dnaChildA->getListGeneticGeneTreeBranch(i);
            std::vector<GeneticGeneTreeBranch *> codeB = dnaChildB->getListGeneticGeneTreeBranch(i);

            GeneticGeneTreeBranch * geneA = codeA[Misc::random(0, codeA.size() - 1)];
            GeneticGeneTreeBranch * geneB = codeB[Misc::random(0, codeB.size() - 1)];

            GeneticGeneTreeBranch * parentGeneA = geneA->getParent();
            GeneticGeneTreeBranch * parentGeneB = geneB->getParent();

            if (parentGeneA != nullptr) {
                auto const begin = std::begin(parentGeneA->getListBranch());
                auto const end = std::end(parentGeneA->getListBranch());
                auto whereGeneA = std::find(begin, end, geneA);

                if (end != whereGeneA) {
                    *whereGeneA = geneB;
                }
            }
            else {
                auto const begin = std::begin(dnaChildA->getListRoot());
                auto const end = std::end(dnaChildA->getListRoot());
                auto whereGeneA = std::find(begin, end, geneA);

                if (end != whereGeneA) {
                    *whereGeneA = geneB;
                }
            }

            if (parentGeneB != nullptr) {
                auto const begin = std::begin(parentGeneB->getListBranch());
                auto const end = std::end(parentGeneB->getListBranch());
                auto whereGeneB = std::find(begin, end, geneB);

                if (end != whereGeneB) {
                    *whereGeneB = geneA;
                }
            }
            else {
                auto const begin = std::begin(dnaChildB->getListRoot());
                auto const end = std::end(dnaChildB->getListRoot());
                auto whereGeneB = std::find(begin, end, geneB);

                if (end != whereGeneB) {
                    *whereGeneB = geneA;
                }
            }

            geneA->setParent(parentGeneB);
            geneB->setParent(parentGeneA);
        }

        couple = new Couple<GeneticDna *, GeneticDna *>((GeneticDna *)dnaChildA, (GeneticDna *)dnaChildB);
    }
    catch (std::bad_cast & e)   {
        Logger::debug(std::string("GeneticDnaTree::cross(): ") + std::string(e.what()));
    }

    return couple;
}

void GeneticDnaTree::destroy() {
    for (GeneticGeneTreeBranch * gene : listRoot) {
        gene->destroy();
    }

    listRoot.clear();
}
#if 0
std::vector<GeneticGeneTreeBranch *> * GeneticDnaTree::getCode() const {
    return &listRoot;
}
#endif

int GeneticDnaTree::getLength() const  {
    return listRoot.size();
}

int GeneticDnaTree::getLength(int index) const {
    return listRoot[index]->getLength();
}

std::vector<GeneticGeneTreeBranch *> * GeneticDnaTree::getListGeneticGeneTreeBranch() const {
    std::vector<GeneticGeneTreeBranch *> * listGene = new std::vector<GeneticGeneTreeBranch *>();

#warning to be finished
#if 0

    for (int i = 0; i < listRoot.size(); i++) {
        listGene->addAll(listRoot[i]->getListGeneticGeneTreeBranch());
    }

#endif
    return listGene;
}

std::vector<GeneticGeneTreeBranch *> GeneticDnaTree::getListGeneticGeneTreeBranch(int index) const {
    return listRoot[index]->getListGeneticGeneTreeBranch();
}

std::vector<GeneticGeneTreeBranch *> & GeneticDnaTree::getListRoot() {
    return listRoot;
}

double GeneticDnaTree::getSimilarityPercent(GeneticDna & other) {
    double percent = 0;

    try {
        GeneticDnaTree & myOther = dynamic_cast<GeneticDnaTree &>(other);

        const int minRoot = std::min(getListRoot().size(), myOther.getListRoot().size());
        const int maxRoot = std::max(getListRoot().size(), myOther.getListRoot().size());

        percent = 100.0;

        for (int j = 0; j < minRoot; j++) {
            std::vector<GeneticGeneTreeBranch *> & listGene1 = *getListGeneticGeneTreeBranch();
            std::vector<GeneticGeneTreeBranch *> & listGene2 = *myOther.getListGeneticGeneTreeBranch();

            int minGene = std::min(listGene1.size(), listGene2.size());
            int maxGene = std::max(listGene1.size(), listGene2.size());

            if (maxGene > 0) {
                int nbSimilarity = 0;

                for (int i = 0; i < minGene; i++) {
                    if (listGene1[i]->equals(*listGene2[i])) {
                        nbSimilarity++;
                    }
                }

                percent = (percent * nbSimilarity) / maxGene;
            }
        }

        if (minRoot != 0 && maxRoot != 0) {
            percent = (percent * minRoot) / maxRoot;
        }
        else {
            percent = 0;
        }
    }
    catch (std::bad_cast & exp)   {
        Logger::debug(std::string("GeneticDnaTree::getSimilarityPercent(): ") + std::string(exp.what()));
    }

    return percent;
}

void GeneticDnaTree::mutate(double chancePerGeneInPercent)  {
    for (size_t index = 0; index < listRoot.size(); index++) {
        for (size_t i = 0; i < getListGeneticGeneTreeBranch(index).size(); i++) {
            if (Misc::random(chancePerGeneInPercent)) {
                getListGeneticGeneTreeBranch(index)[i]->mutate();
            }
        }
    }
}

GeneticDnaTree * GeneticDnaTree::randomDna()  {
    randomDna(1);
    return this;
}

GeneticDnaTree * GeneticDnaTree::randomDna(int size) {
    return this;
}

std::string GeneticDnaTree::toString() const {
    return std::string("GeneticDnaTree::toString()");
}
