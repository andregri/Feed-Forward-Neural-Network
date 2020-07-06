#include "../include/Layer.hpp"
#include "../include/Matrix.hpp"

Layer::Layer(int size)
{
    this->size = size;
    for(int i = 0; i < size; i++) {
        Neuron n(0.00);
        this->neurons.push_back(n);
    }
}

void Layer::setVal(int i, double val)
{
    this->neurons.at(i).setVal(val);
}

Matrix Layer::matrixifyVals()
{
    Matrix m(1, neurons.size(), false);

    for(int i = 0; i < neurons.size(); i++) {
        m.setVal(0, i, neurons.at(i).getVal());
    }

    return m;
}

Matrix Layer::matrixifyActivatedVals()
{
    Matrix m(1, neurons.size(), false);

    for(int i = 0; i < neurons.size(); i++) {
        m.setVal(0, i, neurons.at(i).getActivatedVal());
    }

    return m;
}

Matrix Layer::matrixifyDerivedVals()
{
    Matrix m(1, neurons.size(), false);

    for(int i = 0; i < neurons.size(); i++) {
        m.setVal(0, i, neurons.at(i).getDerivedVal());
    }

    return m;
}