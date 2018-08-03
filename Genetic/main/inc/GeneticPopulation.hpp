#pragma once
#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticIndividual.hpp"
#include "Misc/main/inc/Couple.hpp"
#include "Misc/main/inc/Misc.hpp"
#include <map>
#include <memory>
#include <vector>

class GeneticPopulation {
    public:
        GeneticPopulation();

    public:
        ~GeneticPopulation();

    public:
        void checkAndApplyMutation(GeneticDna * const dna);

    public:
        void checkBloodline(std::shared_ptr<GeneticIndividual> indiv);

    public:
        void generatePopulation(unsigned int number, GeneticDna * dnaType);

    public:
        void generateRandomIndividual();

    public:
        double getAverageScore() const;

    public:
        double getAverageScoreBloodline() const;

    public:
        double getBestScoreEver() const;

    public:
        double getBestScoreInLastGeneration() const;

    public:
        double getBestWeight() const;

    public:
        std::shared_ptr<GeneticIndividual> getBestIndiv();

    public:
        double getBloodlineDnaMinimumDifference() const;

    public:
        double getBloodlineScoreTolerance() const;

    public:
        GeneticDna * getDnaType();

    public:
        int getGenerationNumber() const;

    public:
        std::vector<std::shared_ptr<GeneticIndividual>> & getListBloodline();

    public:
        std::vector<std::shared_ptr<GeneticIndividual>> & getListIndividual();

    public:
        double getMutantPercentChance() const;

    public:
        double getMutationPercentChancePerGene() const;

    public:
        int getNbBloodline() const;

    public:
        double getNewbePercent() const;

    public:
        int getPopulationGoal() const;

    public:
        double getSelectionPercent() const;

    public:
        void killRandomIndividual();

    public:
        void proceedNextGeneration();

    public:
        void proceedEvaluation();

    public:
        void proceedPopulationControl();

    public:
        void proceedReproductionBetweenSelectioned();

    public:
        void proceedReproduction();

    public:
        void proceedSelection();

    public:
        void removeLowestBloodline();

    public:
        void reproduce22(GeneticIndividual & a, GeneticIndividual & b);

    public:
        void reproduce21(const GeneticIndividual & a, const GeneticIndividual & b);

    public:
        void setBestWeight(double bestWeight);

    public:
        void setBloodlineScoreTolerance(double bloodlineScoreTolerance);

    public:
        void setBloodlineDnaMinimumDifference(double bloodlineDnaMinimumDifference);

    public:
        void setDnaType(GeneticDna * dnaType);

    public:
        void setMutantPercentChance(double mutantPercentChance);

    public:
        void setMutationPercentChancePerGene(double mutationPercentChancePerGene);

    public:
        void setNewbePercent(double newbePercent);

    public:
        void setNbBloodline(int nbBloodline);

    public:
        void setPopulationGoal(int populationGoal);

    public:
        void setSelectionPercent(double selectionPercent);

    protected:
        double averageScore;

    protected:
        double averageScoreBloodline;

    protected:
        double bestScoreInLastGeneration;

    protected:
        double bestScoreEver;

    protected:
        double bestWeight;

    protected:
        double bloodlineDnaMinimumDifference;

    protected:
        double bloodlineScoreTolerance;

    protected:
        GeneticDna * dnaType;

    protected:
        int generationNumber;

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listBloodline;

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listIndividual;

    protected:
        std::vector<std::shared_ptr<GeneticIndividual>> listSelection;

    protected:
        std::map<double, std::vector<std::shared_ptr<GeneticIndividual>>> mapScore;

    protected:
        double mutantPercentChance;

    protected:
        double mutationPercentChancePerGene;

    protected:
        unsigned int nbBloodline;

    protected:
        double newbePercent;

    protected:
        unsigned int populationGoal;

    protected:
        double selectionPercent;

    private:
        std::shared_ptr<GeneticIndividual> bestIndiv;
};
