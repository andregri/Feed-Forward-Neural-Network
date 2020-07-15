#include <gtest/gtest.h>
#include "../include/ActivationFunctions.hpp"

#include <cmath>
#include <cstdlib>

class ActivationFunctionsTest : public::testing::Test
{
protected:
    virtual void SetUp() {};
    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(ActivationFunctionsTest, sigmoid)
{
    srand(time(0));
    const double x = rand();
    const double f = 1.0 / (1 + exp(-x));
    ASSERT_DOUBLE_EQ(f, Sigmoid::f(x));
}