#pragma once

#include "Neural/main/inc/NeuralInput.hpp"


class NeuralInputValue : public NeuralInput {
    public:
        NeuralInputValue();

    public:
        NeuralInputValue(double value);

    public:
        virtual ~NeuralInputValue();

    public:
        double getValue() const override;

    public:
        void setValue(const double value);

    private:
        double value;
};
