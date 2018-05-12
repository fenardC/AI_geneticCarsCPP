
#include "Genetic/main/inc/GeneticDnaTreeFormula.hpp"
#include "Genetic/main/inc/GeneticGeneFormulaOperand.hpp"

GeneticDnaTreeFormula::GeneticDnaTreeFormula() {
    /* Add more if needed. */
}

GeneticDnaTreeFormula * GeneticDnaTreeFormula::clone() { /*const*/
    GeneticDnaTreeFormula * dna = new GeneticDnaTreeFormula();

    for (GeneticGeneTreeBranch * root : listRoot) {
        dna->listRoot.push_back(root->clone());
    }

    return dna;
}

GeneticDnaTreeFormula * GeneticDnaTreeFormula::randomDna(int size) {
    listRoot.clear();

    for (int i = 0 ; i < size ; i++) {
        GeneticGeneFormulaOperand * root = new GeneticGeneFormulaOperand();
        root->randomGene();
        listRoot.push_back(root);
    }

    return this;
}

std::string GeneticDnaTreeFormula::toString() const {
    return std::string("GeneticDnaTreeFormula::toString(): TO BE IMPLEMENTED");
}
