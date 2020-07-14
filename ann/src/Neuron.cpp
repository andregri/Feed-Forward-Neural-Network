#include "../include/Neuron.hpp"
#include "../include/ActivationFunctions.hpp"

Neuron::Neuron(ActivationFunction activation_fcn)
{
    this->activation_fcn = activation_fcn;
    setVal(0);
}

void Neuron::setVal(double x)
{
    val = x;
    activatedVal = activation_fcn.f(val);
    derivedVal = activation_fcn.df(val);
}

double Neuron::getVal()
{
    return val;
}

double Neuron::getActivatedVal()
{
    return activatedVal;
}

double Neuron::getDerivedVal()
{
    return derivedVal;
}