#pragma once

#include <string>
#include <vector>

#include "Genetic/main/inc/GeneticGene.hpp"

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
        // ObjectCpp * getValue() override;

    public:
        void mutate() override;

    public:
        virtual GeneticGeneDouble * randomGene();

    public:
        std::string toString() const override;

    protected:
        std::vector<CObject *> code;

    protected:
        int size = 0;

    protected:
        double min = 0;

    protected:
        double max = 0;
};
