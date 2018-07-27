
#pragma once

#include <string>
#include <vector>

class CarParameters final {

    public:
        class NetworkWeights {
            public:
                NetworkWeights(const std::string name, const double value[]);

            private:
                const double * value;

            private:
                std::string name;

            public:
                std::string getName() const;

            public:
                const double * getValue() const;
        };

    public:
        CarParameters();

    public:
        const CarParameters::NetworkWeights * getNext() const;

    private:
        static const double CAR_DNA_77045[];

    private:
        static const double CAR_DNA_100388[];

    private:
        std::vector<NetworkWeights *> parameterList;

        /* Initialize DNA with previously learned cars. */
    private:
        void init();
};
