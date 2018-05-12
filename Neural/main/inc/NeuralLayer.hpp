#pragma once

#include "Neural/main/inc/NeuralNeuron.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"

#include <vector>

class NeuralLayer {
    public:
        NeuralLayer();

    public:
        ~NeuralLayer();

    public:
        NeuralLayer(int nb);

    public:
        NeuralLayer(const NeuralActivation * activationFunction, int nb);

    public:
        void addNeuron(NeuralNeuron * neuron);

    public:
        void calculate() const;

    public:
        void connectAll(NeuralLayer & previousLayer);

    public:
        std::vector<NeuralNeuron *> getListNeuron();

    public:
        void random(double min, double max);

    protected:
        std::vector<NeuralNeuron *> listNeuron;
};
