#pragma once

#include <vector>

#include "Genetic/main/inc/GeneticGene.hpp"

class GeneticGeneObject : public GeneticGene {

    public:
        GeneticGeneObject(std::vector<CObject *> & listPossible);

    public:
        GeneticGeneObject(std::vector<CObject *> & listPossible, int size);

    public:
        virtual ~GeneticGeneObject();

    public:
        virtual GeneticGene * clone() /*const*/ override;

    public:
        virtual void destroy() override;

    public:
        virtual bool equals(const GeneticGene & other) const override;

    public:
        virtual std::vector<CObject *> & getCode();

    public:
        std::vector<CObject *> getListPossible();

    public:
        std::vector<CObject *> & getValue() override;

    public:
        void mutate() override;

    public:
        GeneticGeneObject * randomGene() override;

    public:
        void setListPossible(std::vector<CObject *> & listPossible);

    public:
        virtual std::string toString() const override;

    protected:
        std::vector<CObject *> listPossible;

    protected:
        std::vector<CObject *> code;

    protected:
        int size = 0;
};
