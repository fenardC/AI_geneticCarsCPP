#pragma once
#include "Genetic/main/inc/GeneticGene.hpp"
#include <string>
#include <vector>

class GeneticGeneDouble : public GeneticGene {

    public:
        GeneticGeneDouble(double min, double max);

    public:
        GeneticGeneDouble(double min, double max, int size);

    public:
        virtual ~GeneticGeneDouble();

    public:
        GeneticGene * clone() /*const*/ override;

    public:
        virtual void destroy() override;

    public:
        virtual bool equals(const GeneticGene & other) const override;

    public:
        virtual std::vector<CObject *> & getCode();

    public:
        std::vector<CObject *> & getValue() override;

    public:
        void mutate() override;

    public:
        virtual GeneticGeneDouble * randomGene();

    public:
        std::string toString() const override;

    protected:
        std::vector<CObject *> code;

    protected:
        double max;

    protected:
        double min;

    protected:
        int size;
};
