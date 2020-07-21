#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include <vector>
#include "../include/Layer.hpp"
#include "../include/ActivationFunctions.hpp"
#include "../include/Matrix.hpp"

class NeuralNetwork
{
public:
    NeuralNetwork(int input_size);
    void add_layer(int num_neurons, ActivationFunction fcn);
    void add_layer(int num_neurons, ActivationFunction fcn, Matrix weight, Matrix bias);

    Matrix fprop(std::vector<double> input);
    void bprop();

private:
    int input_size;

    std::vector<Layer> layers;
    std::vector<Matrix> weight_matrixes; // num_rows = size (i+1)-th layer; num_cols = size i-th layer.
    std::vector<Matrix> bias; // column vectors

    void add_weight_matrix();
    void add_weight_matrix(Matrix w);
    void add_bias_matrix();
    void add_bias_matrix(Matrix b);
};

#endif