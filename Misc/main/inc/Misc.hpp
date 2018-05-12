#pragma once

#include <ctime>
#include <cstdlib>
#include <QColor>
#include <QRgb>
#include <map>
#include <memory>
#include <random>


class GeneticIndividual;

class Misc {

    public:
        static void init(void);

    public:
        static double bound(const double val, const int low, const int high);

    public:
        static int mix(const double min, const double max, const double value);

    public:
        static QColor mix(const int fromRgbMin, const int toRgbMax, const double ratio);

    public:
        static bool random(const double chanceInPercent);

    public:
        static double random(const double min, const double max);

    public:
        static int random(const int min, const int max);

    public:
        static const std::shared_ptr<GeneticIndividual> &
        randomInWeightedMap(const std::map<std::shared_ptr<GeneticIndividual>, double> & map);

        /* One single random generator for all random numbers. */
    private:
        static std::mt19937 generator;

    private:
        Misc();
};
