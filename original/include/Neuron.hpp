#ifndef _NEURON_HPP_
#define _NEURON_HPP_

class Neuron
{
public:

    Neuron(double val);

    void setVal(double val);

    // Activation function: fast sigmoid
    // f(x) = 1 / (1 + |x|)
    void activate();

    // Derivative of activation function
    // f'(x) = f(x) * (1 - f(x))
    void derive();

    double getVal() { return this->val; };
    double getActivatedVal() { return this->activateVal; };
    double getDerivedVal() { return this->deriveVal; };

private:
    
    double val;
    double activateVal;
    double deriveVal;
};

#endif //_NEURON_HPP_