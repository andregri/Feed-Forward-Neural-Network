#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include "ActivationFunctions.hpp"

class Neuron
{
public:
    Neuron(ActivationFunction activation_fcn);

    void setVal(double x);

    double getVal();
    double getActivatedVal();
    double getDerivedVal();

private:
    double val;
    double activatedVal;
    double derivedVal;

    ActivationFunction activation_fcn;
};

#endif