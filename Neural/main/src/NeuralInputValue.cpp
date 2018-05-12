
#include "Neural/main/inc/NeuralInputValue.hpp"

NeuralInputValue::NeuralInputValue()
    : NeuralInputValue(0) {
    /* Add more if needed. */
}

NeuralInputValue::NeuralInputValue(double value)
    : ::NeuralInput()
    , value(value) {
}

NeuralInputValue::~NeuralInputValue() {

}

double NeuralInputValue::getValue() const {
    return value;
}

void NeuralInputValue::setValue(const double value) {
    this->value = value;
}
