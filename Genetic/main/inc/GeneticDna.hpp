#pragma once
#include "CObject/main/inc/CObject.hpp"
#include "Debug/main/inc/Logger.hpp"
#include "Misc/main/inc/Couple.hpp"
#include <string>
#include <typeinfo>

class GeneticDna : public CObject {

    public:
        virtual ~GeneticDna() {
            Logger::trace(std::string("GeneticDna::~GeneticDna()<"));
        }

    public:
        virtual GeneticDna * clone() /*const*/ override = 0;

    public:
        virtual Couple<GeneticDna *, GeneticDna *> * cross(GeneticDna & other) = 0;

    public:
        virtual void destroy() = 0;

    public:
        virtual bool equals(const CObject & other) const override = 0;

    public:
        virtual CObject * getCode() const = 0;

    public:
        virtual int getLength() const = 0 ;

    public:
        virtual double getSimilarityPercent(GeneticDna & other) = 0;

    public:
        bool isCompatible(const GeneticDna & other) const {
            return typeid(*this) == typeid(other);
        }

    public:
        virtual void mutate(double chanceInPercent) = 0;

    public:
        virtual GeneticDna * randomDna() = 0;

    public:
        virtual GeneticDna * randomDna(int size) = 0;

    public:
        virtual std::string toString() const override = 0;
};
