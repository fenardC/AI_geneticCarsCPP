#pragma once

class GeneticCrossParameter {
    public:
        static double getCrossRatio();

    private:
        GeneticCrossParameter();

    private:
        static const double CROSS_RATIO;
};
