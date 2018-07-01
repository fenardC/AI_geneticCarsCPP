#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticGeneDouble.hpp"

GeneticDnaNeuralNetwork::GeneticDnaNeuralNetwork(double min, double max, int geneSize, int nbGene)
    : ::GeneticDnaList()
    , geneSize(geneSize)
    , max(max)
    , min(min)
    , nbGene(nbGene) {
}

GeneticDnaNeuralNetwork::~GeneticDnaNeuralNetwork() {
}

GeneticDnaNeuralNetwork * GeneticDnaNeuralNetwork::clone() {
    GeneticDnaNeuralNetwork * dna = new GeneticDnaNeuralNetwork(min, max, geneSize, nbGene);

    for (GeneticGene * const gene : listGene) {
        dna->getListGene().push_back(gene->clone());
    }

    return dna;
}

GeneticDna * GeneticDnaNeuralNetwork::randomDna() {
    return randomDna(nbGene);
}

GeneticDna * GeneticDnaNeuralNetwork::randomDna(int size) {
    listGene.clear();

    for (int i = 0 ; i < size ; i++) {
        GeneticGeneDouble * const geneDouble = new GeneticGeneDouble(min, max, geneSize);
        listGene.push_back(geneDouble->randomGene());
    }

    return this;
}

