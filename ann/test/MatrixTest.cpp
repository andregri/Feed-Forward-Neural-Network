#include <gtest/gtest.h>
#include "../include/Matrix.hpp"

#include <vector>
#include <random>

class MatrixTest : public::testing::Test
{
protected:
    virtual void SetUp() {};
    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(MatrixTest, small_matrix_shape)
{
    // Generate random numbers that can be used for the shape of a matrix
    // stored in the stack, so it can't be too large.

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000);
    int rows = distribution(generator);
    int cols = distribution(generator);
    Matrix m1(rows, cols, true);
    ASSERT_EQ(rows, m1.shape()[0]);
    ASSERT_EQ(cols, m1.shape()[1]);
}

TEST_F(MatrixTest, copy_constructor)
{
    // Create a new matrix a. Then create a second matrix b copying a.

    Matrix a(2,2, true);
    Matrix b(a);

    auto a_shape = a.shape();
    auto b_shape = b.shape();
    for(int i = 0; i < a_shape.size(); ++i) {
        ASSERT_EQ(a_shape[i], b_shape[i]);
    }

    for(int i = 0; i < a.shape()[0]; ++i) {
        for(int j = 0; j < a.shape()[1]; ++j) {
            ASSERT_DOUBLE_EQ(a(i, j), b(i, j));
        }
    }
}

TEST_F(MatrixTest, constructor_fixed_value)
{
    // Create a matrix setting all the elements to a fixed value.

    constexpr double val = 3;
    Matrix m(5, 23, false, val);
    
    for(int i = 0; i < m.shape()[0]; ++i) {
        for(int j = 0; j < m.shape()[1]; ++j) {
            ASSERT_DOUBLE_EQ(m(i, j), val);
        }
    }
}

TEST_F(MatrixTest, matrix_product)
{
    // Multiply a 2x3 matrix and a 3x2 matrix.

    std::vector<std::vector<double>> a_init { {1, 2, 3}, {4, 5, 6} };
    Matrix a(a_init);

    std::vector<std::vector<double>> b_init { {1, 1}, {1, 1}, {1, 1} };
    Matrix b(b_init);

    Matrix actual_c = a * b;
    
    std::vector<std::vector<double>> c_init { {6, 6}, {15, 15} };
    Matrix expected_c(c_init);

    for(int i = 0; i < expected_c.shape()[0]; ++i) {
        for(int j = 0; j < expected_c.shape()[1]; ++j) {
            ASSERT_DOUBLE_EQ(expected_c(i, j), actual_c(i, j));
        }
    }
}