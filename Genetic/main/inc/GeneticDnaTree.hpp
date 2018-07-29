#pragma once
#include "Genetic/main/inc/GeneticDna.hpp"
#include "Genetic/main/inc/GeneticGene.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "Misc/main/inc/Couple.hpp"
#include <string>
#include <vector>

class GeneticDnaTree : public GeneticDna {

    public:
        GeneticDnaTree();

    public:
        virtual ~GeneticDnaTree();

    public:
        virtual GeneticDnaTree * clone() /*const*/ override;

    public:
        virtual Couple<GeneticDna *, GeneticDna *> * cross(GeneticDna & other) override;

    public:
        void destroy() override;

    public:
        virtual bool equals(const CObject & other) const override;

    public:
        CObject * getCode() const override {
            return nullptr;
        }
#if 0
        std::vector<GeneticGeneTreeBranch *> & getCode() const /*override*/;
#endif

    public:
        virtual int getLength() const override;

    public:
        int getLength(int index) const;

    public:
        std::vector<GeneticGeneTreeBranch *> * getListGeneticGeneTreeBranch() const;

    public:
        std::vector<GeneticGeneTreeBranch *> getListGeneticGeneTreeBranch(int index) const;

    public:
        std::vector<GeneticGeneTreeBranch *> & getListRoot();

    public:
        virtual double getSimilarityPercent(GeneticDna & other) override;

    public:
        virtual void mutate(double chancePerGeneInPercent) override;

    public:
        virtual GeneticDnaTree * randomDna() override;

    public:
        virtual GeneticDnaTree * randomDna(int size) override;

    public:
        virtual std::string toString() const override;

    protected:
        std::vector<GeneticGeneTreeBranch *> listRoot;
};
