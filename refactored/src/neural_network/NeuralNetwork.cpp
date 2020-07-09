#include "../../include/NeuralNetwork.hpp"

void NeuralNetwork::setCurrentInput(vector<double> input) {
    this->input = input;

    for(int i = 0; i < input.size(); i++) {
        this->layers.at(0)->setVal(i, input.at(i));
    }
}

NeuralNetwork::NeuralNetwork(vector<int> topology, double bias, double learningRate, double momentum) {
    this->topology = topology;
    this->topologySize = topology.size();
    this->learningRate = learningRate;
    this->momentum = momentum;
    this->bias = bias;

    for(int i = 0; i < topologySize - 1; i++) {
        Matrix *weightMatrix = new Matrix(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(weightMatrix);
    }

    for(int i = 0; i < topology.at(topologySize - 1); i++) {
        errors.push_back(0);
    }

    this->error = 0;
}