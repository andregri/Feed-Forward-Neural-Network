#ifndef _ACTIVATION_FUNCTIONS_HPP_
#define _ACTIVATION_FUNCTIONS_HPP_

#include <cmath>

struct ActivationFunction
{
    double (*f)(double);
    double (*df)(double);
};

class Sigmoid
{
public:
    static double f(double x) {
        return 1.0/(1 + exp(-x));
    }

    static double df(double x) {
        return f(x) * (1 - f(x));
    }
};


#endif