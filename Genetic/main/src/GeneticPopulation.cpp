#include <map>
#include <utility>
#include <vector>
#include <algorithm>

#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Genetic/main/inc/GeneticPopulation.hpp"
#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Misc.hpp"


GeneticPopulation::GeneticPopulation()
    : mapScore()
    , listSelection()
    , populationGoal(0)
    , dnaType(nullptr)
    , mutantPercentChance(50)
    , mutationPercentChancePerGene(50.0)
    , selectionPercent(50.0)
    , newbePercent(5.0)
    , nbBloodline(0)
    , bloodlineScoreTolerance(0.0)
    , bloodlineDnaMinimumDifference(0.0)
    , bestWeight(5.0)
    , listBloodline()
    , averageScore(0.0)
    , averageScoreBloodline(0.0)
    , bestScoreInLastGeneration(-1000000000.0)
    , bestScoreEver(-1000000000.0)
    , generationNumber(1)
    , bestIndiv(nullptr) {
}

void GeneticPopulation::generatePopulation(unsigned int number, GeneticDna * dnaType) {
    populationGoal = number;
    this->dnaType = dnaType;

    for (unsigned int i = 0 ; i < populationGoal ; i++) {
        generateRandomIndividual();
    }
}

void GeneticPopulation::generateRandomIndividual() {
    Logger::trace(std::string("GeneticPopulation::generateRandomIndividual()>"));

    auto indiv = std::make_shared<GeneticIndividual>(dnaType->clone());
    indiv->getDna()->randomDna(dnaType->getLength());
    listIndividual.push_back(indiv);
}

void GeneticPopulation::proceedEvaluation() {
    Logger::trace(std::string("GeneticPopulation::proceedEvaluation()>"));

    mapScore.clear();
    bestScoreInLastGeneration = -1000000000.0;
    std::shared_ptr<GeneticIndividual> bestIndivGen = nullptr;
    double totalScore = 0;

    for (auto indiv : listIndividual) {
        const double score(indiv->getScore());
        totalScore += score;
        Logger::trace(std::string("GeneticPopulation::proceedEvaluation(): totalScore: ") +
                      std::to_string(totalScore));


        if (0 == mapScore.count(score)) {
            Logger::trace(std::string("GeneticPopulation::proceedEvaluation(): indiv->getScore() : ") +
                          std::to_string(indiv->getScore()));
            mapScore[score] = std::vector<std::shared_ptr<GeneticIndividual>>();
        }

        Logger::trace(std::string("GeneticPopulation::proceedEvaluation(): adding indiv for score : ") +
                      std::to_string(score));
        mapScore[score].push_back(indiv);

        if (bestScoreInLastGeneration < score) {
            bestScoreInLastGeneration = score;
            bestIndivGen = indiv;
        }
    }

    if (!listIndividual.empty()) {
        averageScore = totalScore / listIndividual.size();
    }
    else {
        averageScore = totalScore;
    }

    if (bestScoreEver < bestScoreInLastGeneration) {
        bestScoreEver = bestScoreInLastGeneration;
        bestIndiv = std::make_shared<GeneticIndividual>(bestIndivGen);
    }

    /* Adds new bloodlines */
    for (auto indiv : listIndividual) {
        checkBloodline(indiv);
    }

    /* Removes too low scores */
    auto oneBloodLine = listBloodline.begin();
    const double score = bestIndiv->getScore() * (1 - bloodlineScoreTolerance / 100.0);

    while (oneBloodLine != listBloodline.end()) {
        if (score > (*oneBloodLine)->getScore()) {
            listBloodline.erase(oneBloodLine);
        }

        oneBloodLine++;
    }


    /* Removes if too much bloodlines */
    int nbDelete = listBloodline.size() - nbBloodline;

    for (int i = 0 ; i < nbDelete ; i++) {
        removeLowestBloodline();
    }

    if (!listBloodline.empty()) {
        totalScore = 0;

        for (auto indiv : listBloodline) {
            double score(indiv->getScore());
            totalScore += score;
        }

        averageScoreBloodline = totalScore / listBloodline.size();
    }
    else {
        averageScoreBloodline = 0;
    }

    Logger::trace(std::string("GeneticPopulation::proceedEvaluation(): averageScoreBloodline : ")
                  + std::to_string(averageScoreBloodline));
}

void GeneticPopulation::proceedNextGeneration() {
    Logger::trace(std::string("GeneticPopulation::proceedNextGeneration()>"));

    proceedEvaluation();

    proceedSelection();

    proceedReproduction();

    proceedPopulationControl();
    generationNumber++;
    Logger::trace(std::string("GeneticPopulation::proceedNextGeneration()<"));
}

void GeneticPopulation::proceedSelection() {
    Logger::trace(std::string("GeneticPopulation::proceedSelection()>"));

    listSelection.clear();
    /* Taking X% best */
    unsigned int nb = static_cast<unsigned int>(std::ceil(populationGoal * (selectionPercent / 100.0)));

    /* std::map is already sorted, so only needed  to traverse the map using a reverse_iterator */
    auto oneScore = mapScore.rbegin();

    while ((oneScore != mapScore.rend()) && (listSelection.size() < nb)) {
        std::vector<std::shared_ptr<GeneticIndividual>> listIndiv = oneScore->second;

        size_t i = 0;

        while ((i < listIndiv.size()) && (listSelection.size() < nb)) {
            listSelection.push_back(listIndiv[i]);
            i++;
        }

        /* Go on with lower score. */
        oneScore++;
    }

    Logger::trace(std::string("GeneticPopulation::proceedSelection(): listSelection.size(): ") +
                  std::to_string(listSelection.size()));
}

void GeneticPopulation::proceedReproduction() {
    Logger::trace("GeneticPopulation::proceedReproduction()>");

    auto * map = new std::map<std::shared_ptr<GeneticIndividual>, double>();
    double min = 0;
    double max = 0;

    for (size_t i = 0; i < listSelection.size(); i++) {
        const double score = listSelection[i]->getScore();

        if (score > max || i == 0) {
            max = score;
        }

        if (score < min || i == 0) {
            min = score;
        }
    }

    /* [min, max] => [1, bestWeight] */
    for (auto indiv : listSelection) {
        double value = 1.0;

        if (max > min) {
            value = 1 + (bestWeight - 1) * (indiv->getScore() - min) / (max - min);
        }

        map->insert(std::make_pair(indiv, value));
        Logger::trace(std::string("GeneticPopulation::proceedReproduction(): added : ") +
                      std::to_string(value) +
                      std::string(" in map"));
    }

    listIndividual.clear();
    mapScore.clear();

    const int nbNewbe = static_cast<int>(std::ceil(newbePercent / 100 * populationGoal));
    const int nbBlood = listBloodline.size();
    const int nbLess = nbNewbe + nbBlood;

    Logger::trace(std::string("GeneticPopulation::proceedReproduction(): populationGoal : ") + std::to_string(populationGoal));
    Logger::trace(std::string("GeneticPopulation::proceedReproduction(): nbBlood        : ") + std::to_string(nbBlood));
    Logger::trace(std::string("GeneticPopulation::proceedReproduction(): nbLess         : ") + std::to_string(nbLess));
    Logger::trace(std::string("GeneticPopulation::proceedReproduction(): map->size()    : ") + std::to_string(map->size()));

    /* Randomly reproduce */
    for (unsigned int i = 0 ; i < (populationGoal - nbLess) ; i++) {
        auto indiv = Misc::randomInWeightedMap(*map);

        if (nullptr != indiv.get()) {
            auto * map2 = new std::map<std::shared_ptr<GeneticIndividual>, double>(*map);
            map2->erase(indiv);

            if (! map2->empty()) {
                GeneticIndividual & indiv2 = *(Misc::randomInWeightedMap(*map2).get());
                reproduce21(*indiv.get(), indiv2);
            }
        }
    }

    for (int i = 0 ; i < nbBlood ; i++) {
        auto indiv = std::make_shared<GeneticIndividual>(listBloodline[i]);
        indiv->setBloodline(true);
        listIndividual.push_back(indiv);
    }

    for (int i = 0 ; i < nbNewbe ; i++) {
        generateRandomIndividual();
    }

    Logger::trace(std::string("GeneticPopulation::proceedReproduction()<"));
}

void GeneticPopulation::proceedReproductionBetweenSelectioned() {
    Logger::trace(std::string("GeneticPopulation::proceedReproductionBetweenSelectioned()>"));

    listIndividual.clear();
    mapScore.clear();

    /* Randomly reproduce */
    for (auto indiv : listSelection) {
        reproduce22(*indiv, *listSelection[Misc::random(0, listSelection.size() - 1)]);
    }

    Logger::trace(std::string("GeneticPopulation::proceedReproductionBetweenSelectioned()<"));
}


void GeneticPopulation::proceedPopulationControl() {
    Logger::trace("GeneticPopulation::proceedPopulationControl()>");

    if (listIndividual.size() > populationGoal) {
        for (size_t i = 0 ; i < listIndividual.size() - populationGoal ; i++) {
            killRandomIndividual();
        }
    }
    else if (listIndividual.size() < populationGoal) {
        for (size_t i = 0 ; i < populationGoal - listIndividual.size() ; i++) {
            generateRandomIndividual();
        }
    }

    Logger::trace("GeneticPopulation::proceedPopulationControl()<");
}

void GeneticPopulation::killRandomIndividual() {
    Logger::trace(std::string("GeneticPopulation::killRandomIndividual()> "));

    const auto iterator = listIndividual.begin() + Misc::random(0, listIndividual.size() - 1);
    (*iterator)->destroy();
    listIndividual.erase(iterator);
}

void GeneticPopulation::reproduce22(GeneticIndividual & a, GeneticIndividual & b) {
    if (a.getDna()->isCompatible(*b.getDna())) {
        Couple<GeneticDna *, GeneticDna *> * couple = a.getDna()->cross(*b.getDna());

        if (couple != nullptr) {
            GeneticDna * const first = couple->getFirst();
            GeneticDna * const second = couple->getSecond();

            checkAndApplyMutation(first);
            checkAndApplyMutation(second);

            listIndividual.push_back(std::make_shared<GeneticIndividual>(first));
            listIndividual.push_back(std::make_shared<GeneticIndividual>(second));
        }
    }
}

void GeneticPopulation::reproduce21(const GeneticIndividual & a, const GeneticIndividual & b) {
    Logger::trace("GeneticPopulation::reproduce21()>");

    if (a.getDna()->isCompatible(*b.getDna())) {
        Couple<GeneticDna *, GeneticDna *> * const couple = a.getDna()->cross(*b.getDna());

        if (couple != nullptr) {
            GeneticDna * const first = couple->getFirst();
            checkAndApplyMutation(first);
            listIndividual.push_back(std::make_shared<GeneticIndividual>(first));
        }
    }

    Logger::trace("GeneticPopulation::reproduce21()<");
}

void GeneticPopulation::checkAndApplyMutation(GeneticDna * dna) {
    if (Misc::random(mutantPercentChance)) {
        dna->mutate(mutationPercentChancePerGene);
    }
}

void GeneticPopulation::checkBloodline(std::shared_ptr<GeneticIndividual> indiv) {
    Logger::trace("GeneticPopulation::checkBloodline()>");

    if ((nbBloodline > 0) &&
            ((bestIndiv == nullptr) ||
             (bestIndiv->getScore() * (1 - bloodlineScoreTolerance / 100.0) <= indiv->getScore()))) {

        std::shared_ptr<GeneticIndividual> lowest = nullptr;
        size_t lowestIndex = 0;

        if (nbBloodline <= listBloodline.size()) {
            for (lowestIndex = 0 ; lowestIndex < listBloodline.size() ; lowestIndex++) {
                if (lowest == nullptr || lowest->getScore() > listBloodline[lowestIndex]->getScore()) {
                    lowest = listBloodline[lowestIndex];
                }
            }

            if (lowest != nullptr && lowest->getScore() >= indiv->getScore()) {
                return;
            }
        }

        bool ok = true;
        std::vector<std::shared_ptr<GeneticIndividual>> listSimi;

        for (size_t i = 0 ; i < listBloodline.size() ; i++) {
            if (bloodlineDnaMinimumDifference > 100 - indiv->getDna()->getSimilarityPercent(*listBloodline[i]->getDna())) {
                /* Too much similarity */
                if (listBloodline[i]->getScore() < indiv->getScore()) {
                    listSimi.push_back(listBloodline[i]);
                }
                else {
                    return;
                }
            }
        }

        if (ok) {
            if (!listSimi.empty()) {
                for (std::shared_ptr<GeneticIndividual> simi : listSimi) {
                    listBloodline.erase(std::remove(listBloodline.begin(), listBloodline.end(), simi), listBloodline.end());
                }

                listBloodline.push_back(std::make_shared<GeneticIndividual>(indiv));
            }
            else {
                if (nbBloodline <= listBloodline.size()) {
                    listBloodline.erase(listBloodline.begin() + lowestIndex);
                }

                listBloodline.push_back(std::make_shared<GeneticIndividual>(indiv));
            }
        }
    }

    Logger::trace("GeneticPopulation::checkBloodline()<");
}

void GeneticPopulation::removeLowestBloodline() {
    const GeneticIndividual * lowest = nullptr;
    size_t lowestIndex = 0;

    for (lowestIndex = 0 ; lowestIndex < listBloodline.size() ; lowestIndex++) {
        if (lowest == nullptr || lowest->getScore() > listBloodline[lowestIndex]->getScore()) {
            lowest = listBloodline[lowestIndex].get();
        }
    }

    if (lowest != nullptr) {
        listBloodline.erase(listBloodline.begin() + lowestIndex);
    }
}


int GeneticPopulation::getPopulationGoal() {
    return populationGoal;
}

void GeneticPopulation::setPopulationGoal(int populationGoal) {
    this->populationGoal = populationGoal;
}

std::vector<std::shared_ptr<GeneticIndividual>> & GeneticPopulation::getListIndividual() {
    return listIndividual;
}

double GeneticPopulation::getAverageScore() {
    return averageScore;
}

double GeneticPopulation::getBestScoreInLastGeneration() {
    return bestScoreInLastGeneration;
}

double GeneticPopulation::getBestScoreEver() {
    return bestScoreEver;
}

int GeneticPopulation::getGenerationNumber() {
    return generationNumber;
}

GeneticDna * GeneticPopulation::getDnaType() {
    return dnaType;
}

void GeneticPopulation::setDnaType(GeneticDna * dnaType) {
    this->dnaType = dnaType;
}

double GeneticPopulation::getMutantPercentChance() {
    return mutantPercentChance;
}

void GeneticPopulation::setMutantPercentChance(double mutantPercentChance) {
    this->mutantPercentChance = mutantPercentChance;
}

double GeneticPopulation::getMutationPercentChancePerGene() {
    return mutationPercentChancePerGene;
}

void GeneticPopulation::setMutationPercentChancePerGene(double mutationPercentChancePerGene) {
    this->mutationPercentChancePerGene = mutationPercentChancePerGene;
}

std::shared_ptr<GeneticIndividual> GeneticPopulation::getBestIndiv() {
    return bestIndiv;
}

double GeneticPopulation::getNewbePercent() {
    return newbePercent;
}

void GeneticPopulation::setNewbePercent(double newbePercent) {
    this->newbePercent = newbePercent;
}

int GeneticPopulation::getNbBloodline() {
    return nbBloodline;
}

void GeneticPopulation::setNbBloodline(int nbBloodline) {
    this->nbBloodline = nbBloodline;
}

double GeneticPopulation::getBloodlineScoreTolerance() {
    return bloodlineScoreTolerance;
}

void GeneticPopulation::setBloodlineScoreTolerance(double bloodlineScoreTolerance) {
    this->bloodlineScoreTolerance = bloodlineScoreTolerance;
}

double GeneticPopulation::getBloodlineDnaMinimumDifference() {
    return bloodlineDnaMinimumDifference;
}

void GeneticPopulation::setBloodlineDnaMinimumDifference(double bloodlineDnaMinimumDifference) {
    this->bloodlineDnaMinimumDifference = bloodlineDnaMinimumDifference;
}

double GeneticPopulation::getSelectionPercent() {
    return selectionPercent;
}

void GeneticPopulation::setSelectionPercent(double selectionPercent) {
    this->selectionPercent = selectionPercent;
}

double GeneticPopulation::getAverageScoreBloodline() {
    return averageScoreBloodline;
}

std::vector<std::shared_ptr<GeneticIndividual>> & GeneticPopulation::getListBloodline() {
    return listBloodline;
}

double GeneticPopulation::getBestWeight() const {
    return bestWeight;
}

void GeneticPopulation::setBestWeight(double bestWeight) {
    this->bestWeight = bestWeight;
}
