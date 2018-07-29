#pragma once
#include "CObject/main/inc/CInteger.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include <map>
#include <vector>

class GeneticGeneFormulaOperand final : public GeneticGeneTreeBranch {

    public:
        GeneticGeneFormulaOperand();

    public:
        virtual ~GeneticGeneFormulaOperand();

    public:
        GeneticGeneFormulaOperand * clone() /*const*/ override;

    public:
        bool equals(const GeneticGene & other) const override;

    public:
        bool isOperator() const;

    public:
        void mutate() override;

    public:
        GeneticGeneFormulaOperand * randomGene() override;

    public:
        void repareGene();

    public:
        static CInteger getNbOperandForOperator(std::string ope);

    public:
        static void addOperator(std::string ope, CInteger nbOperand);

    public:
        static void addOperand(CInteger operand);

    protected:
        static std::vector<CInteger> listOperandPossible;

    protected:
        static std::vector<std::string> listOperatorPossible;

    protected:
        static std::map<std::string, CInteger> mapNbOperand;
};
