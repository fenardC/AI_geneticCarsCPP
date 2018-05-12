#pragma once

#include "Genetic/main/inc/GeneticDna.hpp"
#include "CObject/main/inc/CObject.hpp"

#include <memory>
#include <sstream>

class GeneticIndividual {
    public:
        GeneticIndividual(GeneticDna * const dna);

    public:
        GeneticIndividual(std::shared_ptr<GeneticIndividual> const indiv);

    public:
        ~GeneticIndividual();

    public:
        void destroy();

    public:
        GeneticDna * getDna() const;

    public:
        double getScore() const;

    public:
        CObject * getTag() const;

    public:
        bool isBloodline() const;

    public:
        void setBloodline(const bool bloodline);

    public:
        void setScore(const double score);

    public:
        void setTag(CObject * const tag);

    public:
        std::string toString() const;

    private:
        double score;

    private:
        bool bloodline;

    private:
        GeneticDna * dna;

    private:
        CObject * tag;
};
