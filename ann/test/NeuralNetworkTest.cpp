#include <gtest/gtest.h>
#include <vector>
#include "../include/NeuralNetwork.hpp"
#include "../include/Matrix.hpp"

class NeuralNetworkTest : public::testing::Test
{
protected:
    virtual void SetUp() {};
    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(NeuralNetworkTest, forward_propagation)
{
    ActivationFunction sigmoid;
    sigmoid.f = Sigmoid::f;
    sigmoid.df = Sigmoid::df;

    // input: 3 neurons
    std::vector<double> input{1, 0, 1};

    NeuralNetwork nn(input.size());

    // layer 0: 2 neurons
    std::vector<std::vector<double>> w0_init{{1, 0.5, 0.25}, {1, 0.5, 0.7}};
    Matrix w0(w0_init);
    std::vector<std::vector<double>> b0_init{{0.8}, {0.3}};
    Matrix b0(b0_init);
    nn.add_layer(2, sigmoid, w0, b0);

    // layer 1: 3 neurons
    std::vector<std::vector<double>> w1_init{{1, 0.7}, {0.9, 0.6}, {0.8, 0.5}};
    Matrix w1(w1_init);
    std::vector<std::vector<double>> b1_init{{1}, {0.5}, {0.2}};
    Matrix b1(b1_init);
    nn.add_layer(3, sigmoid, w1, b1);

    Matrix output = nn.fprop(input);

    // Compute the output manually:
    // expected = sig(a2) =
    //          = sig(W1 * h1 + b1) = 
    //          = sig(W1 * sig(a1) + b1) =
    //          = sig(W1 * sig(W0 * h0 + b0) + b1)
    std::vector<std::vector<double>> h0_init{{1}, {0}, {1}};
    Matrix h0(h0_init);
    Matrix a1 = w0 * h0 + b0;
    Matrix h1 = a1.apply(Sigmoid::f);
    Matrix a2 = w1 * h1 + b1;
    Matrix expected = a2.apply(Sigmoid::f);

    for(int i = 0; i < output.shape()[0]; ++i) {
        ASSERT_DOUBLE_EQ(output(i, 0), expected(i, 0));
    }
}