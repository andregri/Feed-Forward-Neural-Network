#include "../include/Neuron.hpp"
#include <math.h>

Neuron::Neuron(double val)
{
    this->val = val;
    this->activate();
    this->derive();
}

void Neuron::setVal(double val)
{
    this->val = val;
    activate();
    derive();
}

// Activation function: fast sigmoid
// f(x) = x / (1 + |x|)
void Neuron::activate()
{
    this->activateVal = this->val / (1 + abs(this->val));
}

// Derivative of activation function
// f'(x) = f(x) * (1 - f(x))
void Neuron::derive()
{
    this->deriveVal = this->activateVal * (1 - this->activateVal);
}