#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Misc.hpp"


class GeneticPopulation {
    public:
        GeneticPopulation();

    public:
        void generatePopulation(unsigned int number, GeneticDna * dnaType);

    public:
        void generateRandomIndividual();

    public:
        void proceedNextGeneration();

    public:
        void proceedEvaluation();

    public:
        void proceedSelection();

    public:
        void proceedReproductionBetweenSelectioned();

    public:
        void proceedReproduction();

    public:
        void proceedPopulationControl();

    public:
        void killRandomIndividual();

    public:
        void reproduce22(GeneticIndividual & a, GeneticIndividual & b);

    public:
        void reproduce21(const GeneticIndividual & a, const GeneticIndividual & b);

    public:
        void checkAndApplyMutation(GeneticDna * dna);

    public:
        void checkBloodline(std::shared_ptr<GeneticIndividual> indiv);

    public:
        void removeLowestBloodline();

    public:
        int getPopulationGoal();

    public:
        void setPopulationGoal(int populationGoal);

    public:
        std::vector<std::shared_ptr<GeneticIndividual>> & getListIndividual();

    public:
        double getAverageScore();

    public:
        double getBestScoreInLastGeneration();

    public:
        double getBestScoreEver();

    public:
        int getGenerationNumber();

    public:
        GeneticDna * getDnaType();

    public:
        void setDnaType(GeneticDna * dnaType);

    public:
        double getMutantPercentChance();

    public:
        void setMutantPercentChance(double mutantPercentChance);

    public:
        double getMutationPercentChancePerGene();

    public:
        void setMutationPercentChancePerGene(double mutationPercentChancePerGene);

    public:
        std::shared_ptr<GeneticIndividual> getBestIndiv();

    public:
        double getNewbePercent();

    public:
        void setNewbePercent(double newbePercent);

    public:
        int getNbBloodline();

    public:
        void setNbBloodline(int nbBloodline);

    public:
        double getBloodlineScoreTolerance();

    public:
        void setBloodlineScoreTolerance(double bloodlineScoreTolerance);

    public:
        double getBloodlineDnaMinimumDifference();

    public:
        void setBloodlineDnaMinimumDifference(double bloodlineDnaMinimumDifference);

    public:
        double getSelectionPercent();

    public:
        void setSelectionPercent(double selectionPercent);

    public:
        double getAverageScoreBloodline();

    public:
        std::vector<std::shared_ptr<GeneticIndividual>> & getListBloodline();

    public:
        double getBestWeight() const;

    public:
        void setBestWeight(double bestWeight);

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listIndividual;

    protected:
        std::map<double, std::vector<std::shared_ptr<GeneticIndividual>>> mapScore;

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listSelection;

    protected:
        unsigned int populationGoal;

    protected:
        GeneticDna * dnaType;

    protected:
        double mutantPercentChance;

    protected:
        double mutationPercentChancePerGene;

    protected:
        double selectionPercent;

    protected:
        double newbePercent;

    protected:
        unsigned int nbBloodline;

    protected:
        double bloodlineScoreTolerance;

    protected:
        double bloodlineDnaMinimumDifference;

    protected:
        double bestWeight;

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listBloodline;

    protected:
        double averageScore;

    protected:
        double averageScoreBloodline;

    protected:
        double bestScoreInLastGeneration;

    protected:
        double bestScoreEver;

    protected:
        int generationNumber;

    private:
        std::shared_ptr<GeneticIndividual> bestIndiv;
};
