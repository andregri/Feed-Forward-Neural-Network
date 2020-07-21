#include "../include/NeuralNetwork.hpp"
#include <stdexcept>

/**
 * Constructor: define input layer.
 */

NeuralNetwork::NeuralNetwork(int input_size)
{
    this->input_size = input_size;
}

/**
 * Add a layer to the topology specifying number of neurons and activation
 * function.
 */

void NeuralNetwork::add_layer(int num_neurons, ActivationFunction fcn)
{
    // Add the layer.
    layers.emplace_back(num_neurons, fcn);

    // Add the weight matrix randomly initialized.
    add_weight_matrix();

    // Add the bias column vector.
    add_bias_matrix();
}

/**
 * Add a layer to the architecture, but initialize the weight matrix.
 */

void NeuralNetwork::add_layer(int num_neurons, ActivationFunction fcn, Matrix weight, Matrix bias)
{
    // Add the layer.
    layers.emplace_back(num_neurons, fcn);

    // Add the weight matrix randomly initialized.
    add_weight_matrix(weight);

    // Add the bias column vector.
    add_bias_matrix(bias);
}

/**
 * Feed-forward propagation function: take an input, propagates it in the
 * network and returns the output.
 */

Matrix NeuralNetwork::fprop(std::vector<double> input)
{
    if(input.size() != input_size)
        throw std::invalid_argument("Input size must be equal to the input layer size!");

    // Propagate the input to the first layer.
    // Make a column vector from the input:
    Matrix h0(input_size, 1, false, 0);
    for(int i = 0; i < input_size; ++i) {
        h0(i, 0) = input[i];
    }

    // Multiply the first weight matrix to obtain the first input
    Matrix a = weight_matrixes[0] * h0 + bias[0];

    for(int i = 0; i < layers.size() - 1; ++i) {
        layers[i].set_neurons(a);
        Matrix h = layers[i].get_acitvated_neurons();
        a = weight_matrixes[i+1] * h + bias[i+1];
    }
    
    // Get output of the last layer
    int last_layer_index = layers.size() - 1;
    layers[last_layer_index].set_neurons(a);
    Matrix output = layers[last_layer_index].get_acitvated_neurons();

    return output;
}

/**
 * Add a random weight matrix that fits between the last 2 layers.
 * If the network has no layer because it is adding the first layer, then add
 * a matrix that fits the input and the first hidden layer.
 */

void NeuralNetwork::add_weight_matrix()
{
    if(layers.empty())
        throw std::logic_error("First add a layer to the private member layers!");

    int num_cols; // number of neurons in the second last layer.
    if(layers.size() == 1) {
        // adding the first hidden layer.
        num_cols = input_size;
    } else {
        int second_last_layer = layers.size() - 2;
        num_cols = layers[second_last_layer].size();
    }

    int num_rows = layers.back().size(); // number of neurons in the last layer.

    weight_matrixes.emplace_back(num_rows, num_cols, true, 0);
}

/**
 * Add the input matrix to the weight matrixes vector.
 * Check that the matrix fits the network.
 */

void NeuralNetwork::add_weight_matrix(Matrix w)
{
    int num_cols; // number of neurons in the second last layer.
    if(layers.size() == 1) {
        // adding the first hidden layer.
        num_cols = input_size;
    } else {
        int second_last_layer = layers.size() - 2;
        num_cols = layers[second_last_layer].size();
    }

    int num_rows = layers.back().size(); // number of neurons in the last layer.

    // check if the matrix fits in the network.
    if(w.shape()[0] != num_rows || w.shape()[1] != num_cols) {
        throw std::invalid_argument("The weight matrix doesn't fit the last layers.");
    }

    weight_matrixes.push_back(w);
}

/**
 * Add a random bias vector to the network.
 */

void NeuralNetwork::add_bias_matrix()
{
    int num_neurons = layers.back().size();
    bias.emplace_back(num_neurons, 1, true, 0);
}

/**
 * Add the input bias vector to the network.
 * Check if the size is correct.
 */

void NeuralNetwork::add_bias_matrix(Matrix b)
{
    int num_neurons = layers.back().size();
    
    // check if bias has the correct size
    if(b.shape()[0] != num_neurons || b.shape()[1] != 1)
        throw std::invalid_argument("Bias matrix must be as long as the number of neurons.");

    bias.push_back(b);
}