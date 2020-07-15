#include <gtest/gtest.h>
#include "../include/Matrix.hpp"

#include <vector>
#include <cstdlib>

class MatrixTest : public::testing::Test
{
protected:
    virtual void SetUp() {};
    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(MatrixTest, matrix_shape)
{
    srand(time(0));
    int rows = 2;
    int cols = 2;
    Matrix m1(rows, cols, true);
    ASSERT_EQ(rows, m1.shape()[0]);
    ASSERT_EQ(cols, m1.shape()[1]);
}

// TODO: test copy
// TODO: test overloaded operators