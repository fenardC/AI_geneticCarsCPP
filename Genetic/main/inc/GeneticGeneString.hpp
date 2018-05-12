#pragma once

#include "Genetic/main/inc/GeneticGene.hpp"
#include "CObject/main/inc/CString.hpp"
#include "Misc/main/inc/Misc.hpp"

class GeneticGeneString final : public GeneticGene {
    public:
        GeneticGeneString(std::string charset, int size);

    public:
        ~GeneticGeneString();

    public:
        GeneticGene * clone() /*const*/ override;

    public:
        virtual void destroy() override ;

    public:
        bool equals(const GeneticGene & other) const override;

    public:
        std::string & getCharset() /*const*/ ;

    public:
        std::string getCode() const;

    public:
        int getSize() const;

    public:
        std::vector<CObject *> & getValue() override;

    public:
        virtual void mutate() override;

    public:
        virtual GeneticGeneString * randomGene() override;

    public:
        virtual std::string toString() const;

    private:
        std::string charset;

    private:
        std::vector<CObject *> code;

    private:
        int size;
};
