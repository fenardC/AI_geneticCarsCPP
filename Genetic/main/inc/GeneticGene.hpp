#pragma once
#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"
#include <string>
#include <vector>

class GeneticGene : public CObject {

    public:
        virtual ~GeneticGene() {
        }

    public:
        virtual GeneticGene * clone() override = 0;

    public:
        virtual void destroy() = 0;

    public:
        virtual bool equals(const GeneticGene & other) const = 0;

    public:
        bool equals(const CObject & /*other*/) const final override {
            Logger::error(std::string("GeneticGene::equals(): returning false in all cases"));
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
