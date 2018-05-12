#pragma once

#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticDnaList.hpp"

class GeneticDnaNeuralNetwork final : public GeneticDnaList {

    public:
        GeneticDnaNeuralNetwork(double min, double max, int geneSize, int nbGene);

    public:
        ~GeneticDnaNeuralNetwork();

    public:
        GeneticDnaNeuralNetwork * clone() /*const*/ override;

    public:
        GeneticDna * randomDna() override;

    public:
        GeneticDna * randomDna(int size) override;

    private:
        int geneSize;

    private:
        double max;

    private:
        double min;

    private:
        int nbGene;
};
