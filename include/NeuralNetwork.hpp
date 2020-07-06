#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include <iostream>
#include <vector>

#include "Matrix.hpp"
#include "Layer.hpp"

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork(vector<int> topology);
    
    Matrix getWeightMatrix(int i) { return weightMatrices.at(i); };
    
    void setCurrentInput(vector<double> input);
    void setNeuronVal(int indexLayer, int neuronIndex, double val);
    void setLayerVals(int indexLayer, vector<double> neuronVals);

    void feedForward();
    
    void printToConsole();

private:
    int topologySize; 
    vector<int> topology;
    vector<Layer> layers;
    vector<Matrix> weightMatrices;
    vector<double> input;
};

#endif //_NEURAL_NETWORK_HPP