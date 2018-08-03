#pragma once
#include "CObject/main/inc/CDouble.hpp"
#include "Misc/main/inc/Misc.hpp"
#include "Neural/main/inc/NeuralInput.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include <vector>

class NeuralNeuron final : public NeuralInput {

    public:
        NeuralNeuron();

    public:
        NeuralNeuron(const NeuralActivation * activationFunction);

    public:
        virtual ~NeuralNeuron();

    public:
        void addInput(std::shared_ptr<NeuralInput> const input);

    public:
        void calculate();

    public:
        std::vector<std::shared_ptr<NeuralInput>> & getListInput();

    public:
        std::vector<CDouble *> & getListWeight();

    public:
        double getNewOutput() const;

    public:
        double getOutput() const;

    public:
        double getValue() const override;

    public:
        void random(double min, double max);

    public:
        void setActivationFunction(const NeuralActivation * activationFunction);

    public:
        void setOutput(double output);

    public:
        void setThreshold(double threshold);

    private:
        const NeuralActivation * activationFunction;

    private:
        std::vector<std::shared_ptr<NeuralInput>> listInput;

    private:
        std::vector<CDouble *> listWeight;

    private:
        double newOutput;

    private:
        double output;

    private:
        double threshold;
};
