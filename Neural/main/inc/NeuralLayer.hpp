#pragma once
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"
#include <memory>
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
        void addNeuron(std::shared_ptr<NeuralNeuron> neuron);

    public:
        void calculate() const;

    public:
        void connectAll(NeuralLayer & previousLayer);

    public:
        std::vector<std::shared_ptr<NeuralNeuron>> getListNeuron();

    public:
        void random(double min, double max);

    protected:
        std::vector<std::shared_ptr<NeuralNeuron>> listNeuron;
};
