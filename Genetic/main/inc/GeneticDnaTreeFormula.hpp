#pragma once

#include "Genetic/main/inc/GeneticDnaTree.hpp"

#include <string>

class GeneticDnaTreeFormula final : public GeneticDnaTree {

    public:
        GeneticDnaTreeFormula();

    public:
        virtual GeneticDnaTreeFormula * clone() /*const*/ override;

    public:
        virtual GeneticDnaTreeFormula * randomDna(int size) override ;

    public:
        virtual std::string toString() const;
};
