#pragma once

#include <vector>
#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Misc/main/inc/Couple.hpp"

class GeneticDnaList: public GeneticDna {

    public:
        GeneticDnaList();

    public:
        virtual ~GeneticDnaList();

    public:
        GeneticDna * clone() /*const*/ override;

    public:
        Couple<GeneticDna *, GeneticDna *> * cross(GeneticDna & other) override;

    public:
        void destroy() override;

    public:
        virtual bool equals(const CObject & other) const override {
            return false;
        }

    public:
        CObject * getCode() const override {
            return nullptr;
        }

    public:
        int getLength() const override;

    public:
        std::vector<GeneticGene *> & getListGene();

    public:
        double getSimilarityPercent(GeneticDna & other) override;

    public:
        void mutate(double chancePerGeneInPercent) override;

    public:
        virtual GeneticDna * randomDna() override {
            return this;
        }

    public:
        virtual GeneticDna * randomDna(int /*size*/) override {
            return this;
        }

    public:
        std::string toString() const override;

    protected:
        std::vector<GeneticGene *> listGene;
};
