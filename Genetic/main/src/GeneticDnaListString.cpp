
#include "Genetic/main/inc/GeneticDnaListString.hpp"
#include "Genetic/main/inc/GeneticGeneString.hpp"

GeneticDnaListString::GeneticDnaListString(std::string charset, int geneSize)
    : GeneticDnaListString(charset, geneSize, 0) {
}

GeneticDnaListString::GeneticDnaListString(std::string charset, int geneSize, int nbGene)
    : charset(charset)
    , geneSize(geneSize)
    , nbGene(nbGene) {
}

GeneticDnaListString::~GeneticDnaListString() {
}


GeneticDnaListString * GeneticDnaListString::clone() { /*const*/
    GeneticDnaListString * dna = new GeneticDnaListString(charset, geneSize, nbGene);

    for (GeneticGene * gene : GeneticDnaList::listGene) {
        dna->getListGene().push_back(gene->clone());
    }

    return dna;
}

void GeneticDnaListString::destroy() {
    GeneticDnaListObject::destroy();
    charset.clear();
}

std::string GeneticDnaListString::getCharset() const {
    return charset;
}

GeneticDnaListString * GeneticDnaListString::randomDna() {
    return randomDna(nbGene);
}

GeneticDnaListString * GeneticDnaListString::randomDna(int size) {
    listGene.clear();

    for (int i = 0; i < size; i++) {
        GeneticGeneString * p = new GeneticGeneString(charset, geneSize);
        listGene.push_back(p->randomGene());
    }

    return this;
}

