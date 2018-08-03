#pragma once
#include "Genetic/main/inc/GeneticDnaListObject.hpp"
#include <string>

class GeneticDnaListString final : public GeneticDnaListObject {
    public:
        GeneticDnaListString(std::string charset, int geneSize);

    public:
        GeneticDnaListString(std::string charset, int geneSize, int nbGene);

    public:
        virtual ~GeneticDnaListString();

    public:
        GeneticDnaListString * clone() /*const*/ override ;

    public:
        void destroy() override ;

    public:
        std::string getCharset() const ;

    public:
        GeneticDnaListString * randomDna() override ;

    public:
        GeneticDnaListString * randomDna(int size) override ;

    private:
        std::string charset;

    private:
        int geneSize;

    private:
        int nbGene;
};
