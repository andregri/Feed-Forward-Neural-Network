#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>

#include "../include/utils/Math.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"

using namespace std;

int main(int argc, char **argv) {
    vector<double> input;
    input.push_back(0.2);
    input.push_back(0.5);
    input.push_back(0.1);
    input.push_back(0.5);
    input.push_back(0.1);

    vector<double> target;
    target.push_back(0.2);
    target.push_back(0.5);
    target.push_back(0.1);
    target.push_back(0.1);

    double learningRate = 0.05;
    double momentum = 1;
    double bias = 1;
    vector<int> topology;
    topology.push_back(input.size());
    topology.push_back(5);
    topology.push_back(5);
    topology.push_back(target.size());

    NeuralNetwork *nn = new NeuralNetwork(topology);

    for(int i = 0; i < 10; i++) {
        cout << "Training at index " << i << '\t';
        nn->train(input, target, bias, learningRate, momentum);
        double error = nn->getError();
        cout << "Error: " << error << '\n';
    }

    return 0;
}