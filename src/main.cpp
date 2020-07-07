#include <iostream>
#include <vector>

#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"

using namespace std;

int main(int argc, char**argv)
{
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    vector<double> input;
    input.push_back(1.0);
    input.push_back(0.0);
    input.push_back(1.0);

    NeuralNetwork nn(topology);
    nn.setCurrentInput(input);
    nn.setCurrentTarget(input);

    // Training
    for(int i = 0; i < 20; i++) {
        cout << "Epoch: " << i << endl;
        nn.feedForward();
        nn.setErrors();
        nn.backPropagation();
        cout << "Total error: " << nn.getTotalError() << endl;
    }

    return 0;
}