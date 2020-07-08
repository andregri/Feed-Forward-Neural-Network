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
    double getTotalError() { return totalError; };
    
    void setCurrentInput(vector<double> input);
    void setCurrentTarget(vector<double> target);
    void setNeuronVal(int indexLayer, int neuronIndex, double val);
    void setLayerVals(int indexLayer, vector<double> neuronVals);

    void feedForward();
    void backPropagation();
    void setErrors();
    
    void printToConsole();
    void printInputToConsole();
    void printOutputToConsole();
    void printTargetToConsole();
    void printHistoricalErrors();

private:
    int topologySize; 
    vector<int> topology;
    vector<Layer> layers;
    vector<Matrix> weightMatrices;
    vector<Matrix> gradientMatrices;
    vector<double> input;
    vector<double> target;
    double totalError;
    vector<double> errors;
    vector<double> historicalErrors;
};

#endif //_NEURAL_NETWORK_HPP