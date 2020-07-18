/**
 * \brief Simple class to manage matrices.
 * 
 * \details This matrix class will implement only the methods needed by a neural network.
 *          It is implemented using vectors.
 */

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>

class Matrix
{
public:
    Matrix(int num_rows, int num_cols, bool random, double init=0);
    Matrix(const Matrix &m);
    Matrix(std::vector<std::vector<double>> &);

    const double& operator()(int row, int col) const; // get for const objects
    double& operator()(int row, int col);

    std::vector<int> shape() const;

    Matrix operator*(const Matrix &m);

private:
    int num_rows;
    int num_cols;
    std::vector<std::vector<double>> values;

    void set_matrix(double x);
    void set_random_matrix();
};

#endif