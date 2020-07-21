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

TEST_F(MatrixTest, scalar_product)
{

    // row vector of ones 
    Matrix row_vec(1, 6, false, 1);

    // column vector of ones
    Matrix col_vec(6, 1, false, 1);

    Matrix res = row_vec * col_vec;
    ASSERT_EQ(1, res.shape()[0]);
    ASSERT_EQ(1, res.shape()[1]);
    ASSERT_DOUBLE_EQ(6, res(0,0));
}

TEST_F(MatrixTest, matrix_sum)
{
    std::vector<std::vector<double>> a_init { {1, 2, 3}, {4, 5, 6} };
    Matrix a(a_init);

    std::vector<std::vector<double>> b_init { {1, 2, 3}, {4, 5, 6} };
    Matrix b(b_init);

    std::vector<std::vector<double>> res_init { {2, 4, 6}, {8, 10, 12} };
    Matrix expected(res_init);
    Matrix actual = a + b;


    for(int r = 0; r < expected.shape()[0]; ++r) {
        for(int c = 0; c < expected.shape()[1]; ++c) {
            ASSERT_DOUBLE_EQ(expected(r, c), actual(r, c));
        }
    }
}

TEST_F(MatrixTest, matrix_transpose)
{
    // Transpose a matrix
    // 1 2 3 --> 1 4
    // 4 5 6     2 5
    //           3 6

    std::vector<std::vector<double>> a_init { {1, 2, 3}, {4, 5, 6} };
    Matrix a(a_init);
    Matrix b = a.transpose();

    ASSERT_DOUBLE_EQ(1, b(0,0));
    ASSERT_DOUBLE_EQ(2, b(1,0));
    ASSERT_DOUBLE_EQ(3, b(2,0));
    ASSERT_DOUBLE_EQ(4, b(0,1));
    ASSERT_DOUBLE_EQ(5, b(1,1));
    ASSERT_DOUBLE_EQ(6, b(2,1));
}