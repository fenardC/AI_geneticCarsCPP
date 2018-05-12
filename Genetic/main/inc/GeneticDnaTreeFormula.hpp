#pragma once

#include <string>

#include "Genetic/main/inc/GeneticDnaTree.hpp"

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
