#include "../include/Matrix.hpp"
#include <cstdlib>
#include <vector>

/**
 * \brief Constructor for a num_rows x num_cols matrix.
 * 
 * \param[in]   num_rows    Number of rows.
 * \param[in]   num_cols    Number of columns.
 * \param[in]   random      Flag to decide if values are randomly initialized.
 */

Matrix::Matrix(int num_rows, int num_cols, bool random)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    srand(time_t(0));
    for(int r = 0; r < num_rows; ++r)
    {
        std::vector<double> row;
        for(int c = 0; c < num_cols; ++c)
        {
            if(random)
            {
                row.push_back(rand());
            }
            else
            {
                row.push_back(0);
            }
        }
        values.push_back(row);
    }
}

/**
 * \brief Copy constructor.
 * 
 * \param[in]   m       Matrix.
 */

Matrix::Matrix(const Matrix &m)
{
    // TODO: raise exception if shape is different

    for(int r = 0; r < m.shape()[0]; ++r)
    {
        std::vector<double> row;
        for(int c = 0; c < m.shape()[1]; ++c)
        {
            double x = m(r, c);
            row.push_back(m(r, c));
        }
        values.push_back(row);
    }
}

/**
 * \brief Get value from matrix for const objects. The value can't be modified.
 * 
 * \return The reference value of the matrix at r,c.
 */

const double& Matrix::operator()(int r, int c) const
{
    return values[r][c];
}

/**
 * \brief Get and set value of matrix.
 * 
 * \param[in]   r       Row index.
 * \param[in]   c       Column index.
 * 
 * \return The reference of the matrix value at r,c.
 */

double& Matrix::operator()(int r, int c)
{
    return values[r][c];
}

/**
 * \brief Shape of the matrix.
 * 
 * \return Return a vector containing the matrix dimensions.
 */

std::vector<int> Matrix::shape() const
{
    return std::vector<int>{num_rows, num_cols};
}

// TODO: multiplication