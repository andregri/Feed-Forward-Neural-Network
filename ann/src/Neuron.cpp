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
    activated_val = activation_fcn.f(val);
    derived_val = activation_fcn.df(val);
}

double Neuron::get_val()
{
    return val;
}

double Neuron::get_activated_val()
{
    return activated_val;
}

double Neuron::get_derived_val()
{
    return derived_val;
}