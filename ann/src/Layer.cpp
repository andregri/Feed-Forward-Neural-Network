#include "../include/Layer.hpp"

/**
 * \brief Layer constructor.
 * 
 * \details Add neurons to the layer with a specified activation function.
 * 
 * \param[in]   size        Number of neurons in the layer.
 * \param[in]   activ_fcn   Activation function of all the neurons in the layer.
 */

Layer::Layer(int size, ActivationFunction activ_fcn)
{
    num_neurons = size;

    for(int i = 0; i < size; ++i)
    {
        neurons.emplace_back(activ_fcn);
    }
}

/**
 * Return the number of neurons.
 */

int Layer::size()
{
    return num_neurons;
}

/**
 * Set the neuron values
 */

void Layer::set_neurons(Matrix neuron_values)
{
    for(int i = 0; i < neuron_values.shape()[0]; ++i) {
        neurons[i].setVal(neuron_values(i, 0));
    }
}

/**
 * Get a matrix with the activated values produced by neurons
 */

Matrix Layer::get_acitvated_neurons()
{
    Matrix h(num_neurons, 1, false, 0);
    for(int i = 0; i < num_neurons; ++i) {
        h(i, 0) = neurons[i].get_activated_val();
    }
    return h;
}