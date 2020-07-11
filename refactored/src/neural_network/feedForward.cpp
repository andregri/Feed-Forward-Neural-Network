#include "../../include/NeuralNetwork.hpp"
#include "../../include/utils/Math.hpp"

void NeuralNetwork::feedForward() {
    Matrix *a; // matrix of neurons to the left
    Matrix *b; // matrix of weights
    Matrix *c; // matrix of neurons to the right

    for(int i = 0; i < (this->topologySize - 1); i++) {
        if(i != 0) {
            a = this->getActivatedNeuronMatrix(i);
        } else {
            a = this->getNeuronMatrix(i);
        }

        b = this->getWeightMatrix(i);
        c = new Matrix(a->getNumRows(), b->getNumCols(), false);

        utils::Math::multiplyMatrix(a, b, c);

        for(int c_index = 0; c_index < c->getNumCols(); c_index++) {
            this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index) + this->bias);
        }

        delete a;
        delete b;
        delete c;
    }
}