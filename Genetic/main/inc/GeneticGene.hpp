#pragma once

#include <string>
#include <vector>

#include "CObject/main/inc/CObject.hpp"

class GeneticGene : public CObject {

    public:
        virtual ~GeneticGene() {
        }

    public:
        virtual GeneticGene * clone() /*const*/ override = 0;

    public:
        virtual void destroy() = 0;

    public:
        virtual bool equals(const GeneticGene & other) const = 0;

    public:
        bool equals(const CObject & /*other*/) const final override {
            return false;
        };

    public:
        virtual std::vector<CObject *> & getValue() = 0;

    public:
        virtual void mutate() = 0;

    public:
        virtual GeneticGene * randomGene() = 0;

    public:
        virtual std::string toString() const override = 0 ;
};
