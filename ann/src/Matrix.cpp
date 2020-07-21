#include "../include/Matrix.hpp"
#include <random>
#include <vector>
#include <stdexcept>
#include <numeric>

/**
 * Constructor for a (num_rows x num_cols) 2D matrix. If random is true, the 
 * matrix is initialized with random values between 1 and 0, otherwise it is 
 * initialized with init value.
 * 
 * If one dimension is zero, 'invalid argument' exception is raised.
 */

Matrix::Matrix(int num_rows, int num_cols, bool random, double init)
{
    if(num_rows == 0 || num_cols == 0) throw std::invalid_argument("Matrix dimension can't be zero.");

    this->num_rows = num_rows;
    this->num_cols = num_cols;

    if(random)
        set_random_matrix();
    else
        set_matrix(init);
}

/**
 * Copy constructor. Create a new matrix copying the values of the matrix
 * provided as argument.
 */

Matrix::Matrix(const Matrix &m)
{
    num_rows = m.num_rows;
    num_cols = m.num_cols;

    for(int r = 0; r < m.shape()[0]; ++r) {
        std::vector<double> row;
        for(int c = 0; c < m.shape()[1]; ++c) {
            double x = m(r, c);
            row.push_back(m(r, c));
        }
        values.push_back(row);
    }
}

/**
 * Values constructor. Create a new matrix given all the values. Shape of the
 * matrix is infered by the argument.
 */

Matrix::Matrix(std::vector<std::vector<double>> &x)
{
    num_rows = x.size();
    num_cols = x[0].size();

    for(int r = 0; r < num_rows; ++r) {
        if(x.at(r).size() != num_cols)
            throw std::invalid_argument("Rows must have the same number of columns.");
        
        this->values.push_back(x[r]);
    }
}

/**
 * Get value from matrix for const objects. The value can't be modified.
 */

const double& Matrix::operator()(int r, int c) const
{
    return values.at(r).at(c);
}

/**
 * Get the reference to a value of the matrix.
 */

double& Matrix::operator()(int r, int c)
{
    return values.at(r).at(c);
}

/**
 * Return shape of the matrix in a vector of ints.
 */

std::vector<int> Matrix::shape() const
{
    return std::vector<int>{num_rows, num_cols};
}

/**
 * Row-by-column multiplication between two matrices.
 * 
 * If the matrix dimensions don't match (columns of the 1st matrix != rows of
 * the 2nd matrix) raise an exception.
 */

Matrix Matrix::operator*(const Matrix& m2)
{
    if(this->num_cols != m2.shape()[0])
        throw std::invalid_argument("Matrices dimensions don't match for row-by-column product");

    Matrix m(this->num_rows, m2.shape()[1], false, 0);

    for(int r = 0; r < this->num_rows; ++r) {  // loop rows of matrix 1
        for(int c = 0; c < m2.shape()[1]; ++c) { // loop cols of matrix 2
            // multiply the elements of the matrices and sum them
            double product = 0;
            for(int i = 0; i < this->num_cols; ++i) {
                product += ((*this)(r, i) * m2(i, c));
            }
            m(r, c) = product;
        }
    }

    return m;
}

/**
 * Sum between two matrices.
 */

Matrix Matrix::operator+(const Matrix& m)
{
    if(num_rows != m.shape()[0] || num_cols != m.shape()[1])
        throw std::invalid_argument("To sum 2 matrices, they must have the same dimension.");

    Matrix sum(m);
    for(int r = 0; r < m.shape()[0]; ++r) {
        for(int c = 0; c < m.shape()[1]; ++c) {
            sum(r, c) = sum(r, c) + (*this)(r, c);
        }
    }

    return sum;
}

/**
 * Set matrix elements with the same value.
 */

void Matrix::set_matrix(double x)
{
    values = std::vector<std::vector<double>>(
        num_rows, std::vector<double>(num_cols, x));
}

/**
 * Return the transposed matrix.
 */

Matrix Matrix::transpose()
{
    Matrix m(this->num_cols, this->num_rows, false, 0);

    for(int r = 0; r < this->num_rows; ++r) {
        for(int c = 0; c < this->num_cols; ++c) {
            m(c, r) = (*this)(r, c);
        }
    }

    return m;
}

/**
 * Apply a function to each element of the matrix.
 */

Matrix Matrix::apply(double(* fcn)(double x))
{
    Matrix y(num_rows, num_cols, false, 0);

    for(int r = 0; r < num_rows; ++r) {
        for(int c = 0; c < num_cols; ++c) {
            y(r, c) = fcn((*this)(r, c));
        }
    }

    return y;
}

/**
 * Set matrix elements with random values between 0 and 1.
 */

void Matrix::set_random_matrix()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);

    for(int r = 0; r < num_rows; ++r) {
        std::vector<double> row;
        for(int c = 0; c < num_cols; ++c) {
            row.push_back(distribution(generator));
        }
        values.push_back(row);
    }
}