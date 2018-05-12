#pragma once

class NeuralInput {

    public:
        virtual ~NeuralInput() {}

    public:
        virtual double getValue() const = 0;
};
