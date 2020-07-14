#include <iostream>

#include "../include/Neuron.hpp"

int main(int argc, char **argv)
{
    ActivationFunction sigmoid;
    sigmoid.f = Sigmoid::f;
    sigmoid.df = Sigmoid::df;

    Neuron n(sigmoid);

    std::cout << "Neuron1: " << n.getVal() << '\t' << n.getActivatedVal() << '\t' << n.getDerivedVal() << '\n';
}