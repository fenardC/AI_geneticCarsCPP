
#include "Neural/main/inc/NeuralActivation.hpp"
#include "Neural/main/inc/NeuralActivationHeaviside.hpp"
#include "Neural/main/inc/NeuralActivationSigmoid.hpp"

static const NeuralActivationHeaviside heaviside;
static const NeuralActivationSigmoid sigmoid;

const NeuralActivation * NeuralActivation::HEAVISIDE = &heaviside;
const NeuralActivation * NeuralActivation::SIGMOID = &sigmoid;
