#pragma once
#include "Draw/main/inc/Drawer.hpp"
#include "Draw/main/inc/DrawParameterNeuralNetwork.hpp"
#include "Genetic/main/inc/GeneticDnaNeuralNetwork.hpp"
#include "Neural/main/inc/NeuralInput.hpp"
#include "Neural/main/inc/NeuralLayer.hpp"
#include "Neural/main/inc/NeuralNeuron.hpp"
#include <memory>
#include <vector>

class NeuralNetwork {
    public:
        NeuralNetwork();

    public:
        NeuralNetwork(double maxValue);

    public:
        ~NeuralNetwork();

    public:
        void addInput(std::shared_ptr<NeuralInput> const input);

    public:
        void addLayer(std::shared_ptr<NeuralLayer> const layer);

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
        std::vector<std::shared_ptr<NeuralInput>> & getListInput();

    public:
        std::vector<std::shared_ptr<NeuralLayer>> getListLayer() const;

    public:
        std::vector<double> getListResult() const;

    public:
        void setInputValue(const int index, const double value);

    protected:
        std::vector<std::shared_ptr<NeuralInput>> listInput;

    protected:
        std::vector<std::shared_ptr<NeuralLayer>> listLayer;

    protected:
        double maxValue;
};
