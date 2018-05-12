#pragma once

#include "CObject/main/inc/CDouble.hpp"
#include "Neural/main/inc/NeuralInput.hpp"
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Misc/main/inc/Misc.hpp"

#include <vector>


class NeuralNeuron final : public NeuralInput {

    public:
        NeuralNeuron();

    public:
        NeuralNeuron(const NeuralActivation * activationFunction);

    public:
        virtual ~NeuralNeuron();

    public:
        void random(double min, double max);

    public:
        void calculate();

    public:
        void addInput(NeuralInput * const input);

    public:
        void setThreshold(double threshold);

    public:
        void setActivationFunction(const NeuralActivation * activationFunction);

    public:
        std::vector<CDouble *> & getListWeight();

    public:
        std::vector<NeuralInput *> & getListInput();

    public:
        double getOutput() const;

    public:
        void setOutput(double output);

    public:
        double getNewOutput() const;

    public:
        double getValue() const override;

    private:
        double threshold;

    private:
        std::vector<CDouble *> listWeight;

    private:
        std::vector<NeuralInput *> listInput;

    private:
        double output;

    private:
        double newOutput;

    private:
        const NeuralActivation * activationFunction;
};
