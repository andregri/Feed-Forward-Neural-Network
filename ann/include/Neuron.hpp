#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include "ActivationFunctions.hpp"

class Neuron
{
public:
    Neuron(ActivationFunction activation_fcn);

    void setVal(double x);

    double get_val();
    double get_activated_val();
    double get_derived_val();

private:
    double val;
    double activated_val;
    double derived_val;

    ActivationFunction activation_fcn;
};

#endif