#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDnaList.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Genetic/main/inc/GeneticCrossParameter.hpp"
#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <sstream>
#include <typeinfo>
#include <vector>

GeneticDnaList::GeneticDnaList()
    : listGene() {
}

GeneticDnaList::~GeneticDnaList() {
    Logger::trace(std::string("GeneticDnaList::~GeneticDnaList()>"));

    {
        auto deleteGene = [](const GeneticGene * p) {
            std::ostringstream address;
            address << static_cast<void const *>(p);
            Logger::trace(std::string("GeneticDnaList::~GeneticDnaList(): genetic gene: ") + address.str());
            delete p;
        };
        std::for_each(listGene.begin(), listGene.end(), deleteGene);
        listGene.clear();
    }

    Logger::trace(std::string("GeneticDnaList::~GeneticDnaList()<"));
}

GeneticDnaList * GeneticDnaList::clone() { /*const*/
    GeneticDnaList * dna = new GeneticDnaList();

    for (const auto gene : GeneticDnaList::listGene) {
        dna->getListGene().push_back(gene->clone());
    }

    return dna;
}

Couple<GeneticDna *, GeneticDna *> * GeneticDnaList::cross(GeneticDna & other) {
    Couple<GeneticDna *, GeneticDna *> * couple(nullptr);
    Logger::trace(std::string("GeneticDnaList::cross()>"));

    try {
        GeneticDnaList & b = dynamic_cast<GeneticDnaList &>(other);

        std::vector<GeneticGene *> codeA = listGene;
        std::vector<GeneticGene *> codeB = b.getListGene();

        const size_t maxLength = std::max(codeA.size(), codeB.size());
        const size_t sizeCross = (maxLength * GeneticCrossParameter::getCrossRatio());
        const size_t indexCross = Misc::random(1, maxLength - sizeCross);

        std::vector<GeneticGene *> startA;
        std::vector<GeneticGene *> endA;

        if (indexCross < codeA.size()) {
            // endA.addAll(codeA.subList(indexCross, codeA.size()));
            std::vector<GeneticGene *> firstPart(codeA.begin() + indexCross, codeA.begin() + codeA.size());
            endA = firstPart;

            // startA.addAll(codeA.subList(0, indexCross));
            std::vector<GeneticGene *> secondPart(codeA.begin(), codeA.begin() + indexCross);
            startA = secondPart;
        }
        else {
            startA = codeA;
        }

        std::vector<GeneticGene *> startB;
        std::vector<GeneticGene *> endB;

        if (indexCross < codeB.size()) {
            // endB.addAll(codeB.subList(indexCross, codeB.size()));
            std::vector<GeneticGene *> firstPart(codeB.begin() + indexCross, codeB.begin() + codeB.size());
            endB = firstPart;

            // startB.addAll(codeB.subList(0, indexCross));
            std::vector<GeneticGene *> secondPart(codeB.begin(), codeB.begin() + indexCross);
            startB = secondPart;
        }
        else {
            startB = codeB;
        }

        GeneticDnaList * dnaChildA = static_cast<GeneticDnaList *>(clone());
        dnaChildA->getListGene().clear();

        for (GeneticGene * gene : startA) {
            dnaChildA->getListGene().push_back(gene->clone());
        }

        for (GeneticGene * gene : endB) {
            dnaChildA->getListGene().push_back(gene->clone());
        }

        GeneticDnaList * dnaChildB = static_cast<GeneticDnaList *>(b.clone());
        dnaChildB->getListGene().clear();

        for (GeneticGene * gene : startB) {
            dnaChildB->getListGene().push_back(gene->clone());
        }

        for (GeneticGene * gene : endA) {
            dnaChildB->getListGene().push_back(gene->clone());
        }

        couple = new Couple<GeneticDna *, GeneticDna *>(static_cast<GeneticDna *>(dnaChildA), static_cast<GeneticDna *>(dnaChildB));
    }
    catch (std::bad_cast & exp)   {
        Logger::error(std::string("GeneticDnaList::cross(): ") + std::string(exp.what()));
    }

    return couple;
}

void GeneticDnaList::destroy() {
    Logger::trace(std::string("GeneticDnaList::destroy()>"));

    for (auto * const gene : listGene) {
        gene->destroy();
    }

    listGene.clear();
    Logger::trace(std::string("GeneticDnaList::destroy()<"));
}

bool GeneticDnaList::equals(const CObject & other) const {
    bool result = false;

    try {
        const GeneticDnaList & myOther = const_cast<GeneticDnaList &>(dynamic_cast<const GeneticDnaList & >(other));
        const size_t size = listGene.size();
        const size_t myOtherSize = myOther.listGene.size();

        if (size == myOtherSize) {
            result = true;

            for (size_t i = 0; i < size; i++) {
                if (listGene[i] != (myOther.listGene[i])) {
                    result = false;
                    break;
                }
            }
        }
    }
    catch (const std::bad_cast & e) {
        Logger::error(std::string("GeneticDnaList::equals(): ") + std::string(e.what()));
    }

    return result;
}

#warning to be fixed
#if 0
std::vector<GeneticGene *> & GeneticDnaList::getCode() {
    return listGene;
}
#endif

int GeneticDnaList::getLength() const {
    return listGene.size();
}

std::vector<GeneticGene *> & GeneticDnaList::getListGene() {
    return listGene;
}

double GeneticDnaList::getSimilarityPercent(GeneticDna & other) {
    double percent = 0;

    try {
        GeneticDnaList & myOther = dynamic_cast<GeneticDnaList &>(other);

        int minGene = std::min(myOther.getListGene().size(), getListGene().size());
        int maxGene = std::max(myOther.getListGene().size(), getListGene().size());

        if (maxGene > 0) {
            int nbSimilarity = 0;

            for (int i = 0; i < minGene; i++) {
                if (myOther.getListGene()[i]->equals(*getListGene()[i])) {
                    nbSimilarity++;
                }
            }

            percent = nbSimilarity / (double) maxGene * 100.0;
        }
    }
    catch (std::bad_cast & exp)   {
        Logger::error(std::string("GeneticDnaList::getSimilarityPercent(): ") + std::string(exp.what()));
    }

    return percent;
}

void GeneticDnaList::mutate(double chancePerGeneInPercent) {
    for (size_t i = 0 ; i < listGene.size() ; i++) {
        if (Misc::random(chancePerGeneInPercent)) {
            listGene[i]->mutate();
        }
    }
}

std::string GeneticDnaList::toString() const {
    std::stringstream result;

    for (size_t i = 0 ; i < listGene.size() ; i++) {
        if (i > 0) {
            result << ", ";
        }

        result << listGene[i]->toString();
    }

    return result.str();
}
