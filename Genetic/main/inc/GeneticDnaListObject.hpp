#pragma once
#include "Genetic/main/inc/GeneticDnaList.hpp"
#include <vector>

class GeneticDnaListObject : public GeneticDnaList {

    public:
        GeneticDnaListObject();

    public:
        GeneticDnaListObject(const std::vector<CObject *> & listPossible, int geneSize);

    public:
        GeneticDnaListObject(const std::vector<CObject *> & listPossible, int geneSize, int nbGene);

    public:
        virtual ~GeneticDnaListObject();

    public:
        virtual GeneticDnaListObject * clone() /*const*/ override;

    public:
        void destroy() override;

    public:
        std::vector<CObject *> getListPossible() const;

    public:
        GeneticDnaListObject * randomDna() override;

    public:
        GeneticDnaListObject * randomDna(int size) override;

    private:
        int geneSize;

    private:
        std::vector<CObject *> listPossible;

    private:
        int nbGene;
};
