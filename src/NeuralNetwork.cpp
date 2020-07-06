#include <iostream>
#include <vector>

#include "../include/NeuralNetwork.hpp"
#include "../include/Layer.hpp"

using namespace std;

NeuralNetwork::NeuralNetwork(vector<int> topology)
{
    // initialize the topology: the number of layers and the number of neurons
    // in each layer.
    this->topologySize = topology.size();
    for(int i = 0; i < topologySize; i++) {
        Layer l(topology.at(i));
        this->layers.push_back(l);
    }

    // initialize the weight matrix between layer i and layer i+1
    for(int i = 0; i < (topologySize -1); i++) {
        Matrix m(topology.at(i), topology.at(i+1), true);
        this->weightMatrices.push_back(m);
    }
}

void NeuralNetwork::setCurrentInput(vector<double> input)
{
    this->input = input;
    
    for(int i = 0; i < input.size(); i++) {
        this->layers.at(0).setVal(i, input.at(i));
    }
}

void NeuralNetwork::setNeuronVal(int indexLayer, int neuronIndex, double val)
{
    layers.at(indexLayer).setVal(neuronIndex, val);
}

void NeuralNetwork::setLayerVals(int indexLayer, vector<double> neuronVals)
{
    for(int i = 0; i < neuronVals.size(); i++) {
        setNeuronVal(indexLayer, i, neuronVals.at(i));
    }
}

void NeuralNetwork::feedForward()
{
    // compute the output of the first hidden layer
    Matrix layer_input = layers.at(0).matrixifyVals();
    Matrix layer_output = layer_input * getWeightMatrix(0);
    setLayerVals(1, layer_output.toVector());

    // compute the output of all the hidden layers and of the output layer
    for(int l = 1; l < (layers.size() - 1); l++)
    {
        layer_input = layers.at(l).matrixifyActivatedVals();
        layer_output = layer_input * getWeightMatrix(l);
        setLayerVals(l+1, layer_output.toVector());
    }
}

void NeuralNetwork::printToConsole()
{
    for(int i = 0; i < this->layers.size(); i++) {
        cout << "LAYER: " << i << endl;
        if(i == 0) {
            Matrix m = this->layers.at(i).matrixifyVals();
            m.printToConsole();
        } else {
            Matrix m = this->layers.at(i).matrixifyActivatedVals();
            m.printToConsole();
        }
        cout << "========================" << endl;
        if(i < layers.size() - 1) {
            cout << "Weight matrix between layer " << i << 
            " and layer " << i + 1 << endl;
            getWeightMatrix(i).printToConsole();
        }
        cout << "========================" << endl;
    }
}