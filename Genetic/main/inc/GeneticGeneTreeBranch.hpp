#pragma once

#include <vector>

#include "Genetic/main/inc/GeneticGeneObject.hpp"
#include "Misc/main/inc/Misc.hpp"

class GeneticGeneTreeBranch : public GeneticGeneObject {
    public:
        GeneticGeneTreeBranch(std::vector<CObject *> & listPossible);

    public:
        virtual ~GeneticGeneTreeBranch();

    public:
        virtual GeneticGeneTreeBranch * clone() /*const*/ override;

    public:
        void destroy() override;

    public:
        virtual bool equals(const GeneticGene & other) const override;

    public:
        int getLength() const;

    public:
        std::vector<GeneticGeneTreeBranch *> & getListBranch();

    public:
        std::vector<GeneticGeneTreeBranch *> getListGeneticGeneTreeBranch();

    public:
        GeneticGeneTreeBranch * getParent() const;


    public:
        void setParent(GeneticGeneTreeBranch * const parent);

    protected:
        std::vector<GeneticGeneTreeBranch *> listBranch;

    protected:
        GeneticGeneTreeBranch * parent;
};
