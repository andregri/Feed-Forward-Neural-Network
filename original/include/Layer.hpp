#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>

#include "Neuron.hpp"
#include "Matrix.hpp"

using namespace std;

class Layer
{
public:
    Layer(int size);

    void setVal(int i, double v);
    int getSize() { return size; };

    Matrix matrixifyVals();
    Matrix matrixifyActivatedVals();
    Matrix matrixifyDerivedVals();

private:
    int size;
    vector<Neuron> neurons;
};

#endif  //_LAYER_HPP_