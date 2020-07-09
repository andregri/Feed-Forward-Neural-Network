#include <iostream>
#include <vector>
#include <algorithm>

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

    // initialize errors vector
    int outputLayerIndex = topologySize - 1;
    int numOutputNeurons = topology.at(outputLayerIndex);
    for(int i = 0; i < numOutputNeurons; i++) {
        errors.push_back(0);
    }
}

void NeuralNetwork::setCurrentInput(vector<double> input)
{
    this->input = input;
    
    for(int i = 0; i < input.size(); i++) {
        this->layers.at(0).setVal(i, input.at(i));
    }
}

void NeuralNetwork::setCurrentTarget(vector<double> target)
{
    this->target = target;
    
    for(int i = 0; i < target.size(); i++) {
        this->layers.at(0).setVal(i, target.at(i));
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

void NeuralNetwork::backPropagation()
{
    vector<Matrix> newWeights;

    // output to hidden
    int outputLayerIndex = layers.size() - 1;
    Matrix outputDerivedVals = layers.at(outputLayerIndex).matrixifyDerivedVals();
    Matrix gradientYtoZ(1, layers.at(outputLayerIndex).getSize(), false);

    for(int i = 0; i < errors.size(); i++) {
        double derivedVal = outputDerivedVals.getVal(0, i);
        double error = errors.at(i);
        double g = derivedVal * error;
        gradientYtoZ.setVal(0, i, g);
    }

    int lastHiddenLayerIndex    = outputLayerIndex - 1;
    Layer lastHiddenLayer       = layers.at(lastHiddenLayerIndex);
    Matrix weightOutputToHidden   = weightMatrices.at(lastHiddenLayerIndex);
    Matrix deltaOutputToHidden  =   (gradientYtoZ.transpose() *
                                    lastHiddenLayer.matrixifyActivatedVals())
                                    .transpose();
    Matrix newWeightsOutputToHidden(deltaOutputToHidden.getNumRows(),
                                    deltaOutputToHidden.getNumCols(),
                                    false);

    for(int r = 0; r < deltaOutputToHidden.getNumRows(); r++) {
        for(int c = 0; c < deltaOutputToHidden.getNumCols(); c++) {
            double originalWeight = weightOutputToHidden.getVal(r, c);
            double deltaWeight = deltaOutputToHidden.getVal(r, c);
            newWeightsOutputToHidden.setVal(r, c, originalWeight - deltaWeight);
        }
    }

    newWeights.push_back(newWeightsOutputToHidden);

    //cout << "Output to hidden new weights: " << endl;
    //newWeightsOutputToHidden.printToConsole();

    Matrix gradient(gradientYtoZ.getNumRows(),
                    gradientYtoZ.getNumCols(),
                    false);
    for(int r = 0; r < gradientYtoZ.getNumRows(); r++) {
        for(int c = 0; c < gradientYtoZ.getNumCols(); c++) {
            gradient.setVal(r, c, gradientYtoZ.getVal(r, c));
        }
    }

    // moving from the last hidden layer down to input layer
    for(int i = lastHiddenLayerIndex; i > 0; i--) {
        Layer layer = layers.at(i);

        Matrix derivedHidden  = layer.matrixifyDerivedVals();
        Matrix activatedHiddenVals = layer.matrixifyActivatedVals();

        Matrix derivedGradients(1, layer.getSize(), false);

        Matrix weightMatrix = weightMatrices.at(i);
        Matrix originalWeights = weightMatrices.at(i - 1);

        for(int r = 0; r < weightMatrix.getNumRows(); r++) {
            double sum = 0;

            for(int c = 0; c < weightMatrix.getNumCols(); c++) {
                double p = gradient.getVal(0, c) * weightMatrix.getVal(r, c);
                sum += p;
            }

            double g = sum * activatedHiddenVals.getVal(0, r);
            derivedGradients.setVal(0, r, g);
        }

        Matrix leftNeurons = (i - 1) ? layers.at(0).matrixifyVals() :
                                       layers.at(i-1).matrixifyActivatedVals();

        Matrix deltaWeights =   (derivedGradients.transpose() *
                                leftNeurons).transpose();

        Matrix newWeightsHidden(  deltaWeights.getNumRows(),
                            deltaWeights.getNumCols(), 
                            false);

        for(int r = 0; r < newWeightsHidden.getNumRows(); r++) {
            for(int c = 0; c < newWeightsHidden.getNumCols(); c++) {
                double originalWeight = originalWeights.getVal(r, c);
                double deltaWeight = deltaWeights.getVal(r, c);
                newWeightsHidden.setVal(r, c, originalWeight - deltaWeight);
            }
        }

        Matrix gradient(derivedGradients.getNumRows(),
                        derivedGradients.getNumCols(),
                        false);
        for(int r = 0; r < derivedGradients.getNumRows(); r++) {
            for(int c = 0; c < derivedGradients.getNumCols(); c++) {
                gradient.setVal(r, c, derivedGradients.getVal(r, c));
            }
        }
        
        newWeights.push_back(newWeightsHidden);
    }

    cout << "Done with back prop" << endl;

    reverse(newWeights.begin(), newWeights.end());
    weightMatrices = newWeights;
}

void NeuralNetwork::setErrors()
{
    totalError = 0;
    int outputLayerIndex = layers.size() - 1;
    Matrix outputVals = layers.at(outputLayerIndex).matrixifyActivatedVals();

    for(int i = 0; i < target.size(); i++) {
        double err = outputVals.getVal(0, i) - target.at(i);
        errors.at(i) = err;
        totalError += pow(err, 2);  // quadratic cost function
    }

    totalError /= 2;
    historicalErrors.push_back(totalError);
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

void NeuralNetwork::printInputToConsole()
{
    for(int i = 0; i < input.size(); i++) {
        cout << input.at(i) << "\t\t";
    }
}

void NeuralNetwork::printTargetToConsole()
{
    for(int i = 0; i < target.size(); i++) {
        cout << target.at(i) << "\t\t";
    }
}

void NeuralNetwork::printOutputToConsole()
{
    int outputLayerIndex = layers.size() - 1;
    Matrix outputValues = layers.at(outputLayerIndex).matrixifyActivatedVals();
    for(int i = 0; i < outputValues.getNumCols(); i++) {
        cout << outputValues.getVal(0, i) << "\t\t";
    }
}

void NeuralNetwork::printHistoricalErrors()
{
    for(int i = 0; i < historicalErrors.size(); i++) {
        cout << historicalErrors.at(i);
        if(i != historicalErrors.size() - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}