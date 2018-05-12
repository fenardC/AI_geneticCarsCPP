#pragma once

#include <vector>

#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Draw/main/inc/Drawer.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Neural/main/inc/NeuralInput.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"


class NeuralNetwork {
    public:
        NeuralNetwork();

    public:
        NeuralNetwork(double maxValue);

    public:
        ~NeuralNetwork();

    public:
        void initFromDna(GeneticDnaNeuralNetwork & dna);

    public:
        GeneticDnaNeuralNetwork * generateDnaModel();

    public:
        void render(Drawer & d, double x, double y, DrawParameterNeuralNetwork param) const;

    public:
        void random();

    public:
        void calculate();

    public:
        void connectAllInputOnFirstLayer();

    public:
        void addLayer(NeuralLayer * const layer);

    public:
        std::vector<NeuralLayer *> getListLayer() const;

    public:
        void addInput(NeuralInput * const input);

    public:
        void setInputValue(const int index, const double value);

    public:
        std::vector<double> getListResult() const;

    public:
        std::vector<NeuralInput *> & getListInput();

    protected:
        std::vector<NeuralInput *> listInput;

    protected:
        std::vector<NeuralLayer *> listLayer;

    protected:
        double maxValue;
};
