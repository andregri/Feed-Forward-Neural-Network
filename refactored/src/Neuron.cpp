#include "../include/Neuron.hpp"

void Neuron::setVal(double val) {
    this->val = val;
    activate();
    derive();
}

void Neuron::activate() {
    switch(activationType) {
        case TANH:
            activatedVal = tanh(val);
            break;
        
        case RELU:
            if(val > 0) activatedVal = val;
            else activatedVal = 0;
            break;

        case SIGM:
        default:
            activatedVal = 1 / (1 + exp(-val));
            break;
    }
}

void Neuron::derive() {
        switch(activationType) {
        case TANH:
            derivedVal = 1 - pow(activatedVal, 2);
            break;
        
        case RELU:
            if(val > 0) derivedVal = 1;
            else derivedVal = 0;
            break;

        case SIGM:
        default:
            derivedVal = activatedVal * (1 - activatedVal);
            break;
        }
}

// Constructor
Neuron::Neuron(double val) {
    setVal(val);
}

Neuron::Neuron(double val, int activationType) {
    setVal(val);
    this->activationType = activationType;
}