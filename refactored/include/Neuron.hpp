#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#define TANH 1
#define RELU 2
#define SIGM 3

#include <iostream>
#include <math.h>

using namespace std;

class Neuron
{
public:
    Neuron(double val);
    Neuron(double val, int activationType);

    // setter
    void setVal(double val);
    
    void activate();
    void derive();

    //getter
    double getVal() { return this->val; };
    double getActivatedVal() { return this->activatedVal; };
    double getDerivedVal() { return this->derivedVal; };

private:
    double val;
    double activatedVal;
    double derivedVal;

    int activationType = 3; //default is SIGMOID
};

#endif //_NEURON_HPP_