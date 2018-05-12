#pragma once

class NeuralActivation {
    public:
        static const NeuralActivation * HEAVISIDE;

    public:
        static const NeuralActivation * SIGMOID;

    public:
        virtual ~NeuralActivation() {}

    public:
        virtual double calculate(double value) const = 0 ;
};
