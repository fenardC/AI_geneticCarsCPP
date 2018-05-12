#pragma once

#include "Neural/main/inc/NeuralActivation.hpp"
#include <cmath>

class NeuralActivationSigmoid final : public NeuralActivation {

    public:
        NeuralActivationSigmoid()
            : ::NeuralActivation() {
        }

    public:
        virtual ~NeuralActivationSigmoid() {
        }

    public:
        double calculate(const double value) const {
            return 1 / (1 + std::exp(-value));
        }
};
