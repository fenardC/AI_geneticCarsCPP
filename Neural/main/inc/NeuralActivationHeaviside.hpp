#pragma once

#include "Neural/main/inc/NeuralActivation.hpp"

class NeuralActivationHeaviside final : public NeuralActivation {

    public:
        NeuralActivationHeaviside()
            : ::NeuralActivation() {
        }

    public:
        virtual ~NeuralActivationHeaviside() {
        }

    public:
        double calculate(const double value) const {
            return value >= 0 ? 1 : 0;
        }
};
