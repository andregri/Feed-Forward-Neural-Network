/**
 * \brief Layer is an aggregation of neurons with the same activation function.
 * 
 */

#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <vector>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"

class Layer
{
public:
    Layer(int size, ActivationFunction activ_fcn);
    int size();
    void set_neurons(Matrix neuron_values);
    Matrix get_acitvated_neurons();

private:
    int num_neurons;
    std::vector<Neuron> neurons;
};

#endif