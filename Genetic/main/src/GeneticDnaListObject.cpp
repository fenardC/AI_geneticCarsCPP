
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include "Genetic/main/inc/GeneticGeneObject.hpp"

GeneticDnaListObject::GeneticDnaListObject()
    : listPossible()
    , geneSize(0)
    , nbGene(0) {
}

GeneticDnaListObject::GeneticDnaListObject(const std::vector<CObject *> & listPossible, int geneSize)
    : GeneticDnaListObject(listPossible, geneSize, 0) {

}

GeneticDnaListObject::GeneticDnaListObject(const std::vector<CObject *> & listPossible, int geneSize, int nbGene)
    : listPossible()
    , geneSize(geneSize)
    , nbGene(nbGene) {
    for (CObject * const o : listPossible) {
        this->listPossible.push_back(o);
    }
}

GeneticDnaListObject::~GeneticDnaListObject() {
}

GeneticDnaListObject * GeneticDnaListObject::clone() { /*const*/
    GeneticDnaListObject * dna = new GeneticDnaListObject(listPossible, geneSize, nbGene);

    for (GeneticGene * gene : GeneticDnaList::listGene) {
        dna->getListGene().push_back(gene->clone());
    }

    return dna;
}

void GeneticDnaListObject::destroy() {
    GeneticDnaList::destroy();
    listPossible.clear();
}

std::vector<CObject *> GeneticDnaListObject::getListPossible() const {
    return listPossible;
}

GeneticDnaListObject * GeneticDnaListObject::randomDna() {
    return randomDna(nbGene);
}

GeneticDnaListObject * GeneticDnaListObject::randomDna(int size) {
    listGene.clear();

    for (int i = 0 ; i < size ; i++) {
        GeneticGeneObject * p = new GeneticGeneObject(listPossible, geneSize);
        listGene.push_back(p->randomGene());
    }

    return this;
}
