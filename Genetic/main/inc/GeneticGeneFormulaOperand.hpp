#pragma once
#include "CObject/main/inc/CInteger.hpp"
#include "CObject/main/inc/CString.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include <map>
#include <vector>

class GeneticGeneFormulaOperand final : public GeneticGeneTreeBranch {

    public:
        GeneticGeneFormulaOperand();

    public:
        virtual ~GeneticGeneFormulaOperand();

    public:
        static void addOperator(CString ope, CInteger nbOperand);

    public:
        static void addOperand(CInteger operand);

    public:
        GeneticGeneFormulaOperand * clone() /*const*/ override;

    public:
        bool equals(const GeneticGene & other) const override;

    public:
        static CInteger getNbOperandForOperator(CString ope);

    public:
        bool isOperator() const;

    public:
        void mutate() override;

    public:
        GeneticGeneFormulaOperand * randomGene() override;

    public:
        void repareGene();

    protected:
        static std::vector<CInteger> listOperandPossible;

    protected:
        static std::vector<CString> listOperatorPossible;

    protected:
        static std::map<CString, CInteger, CString::Compare> mapNbOperand;
};
