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
    for(int i = 0; i < size; ++i)
    {
        neurons.emplace_back(activ_fcn);
    }
}