/**
 * \brief Layer is an aggregation of neurons with the same activation function.
 * 
 */

#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <vector>
#include "../include/Neuron.hpp"

class Layer
{
public:
    Layer(int size, ActivationFunction activ_fcn);

private:
    std::vector<Neuron> neurons;
};

#endif