#include <stdexcept>

#include "../include/Matrix.hpp"

Matrix::Matrix(int numRows, int numCols, bool isRandom)
{
    this->numRows = numRows;
    this->numCols = numCols;

    for(int i = 0; i < numRows; i++) {
        vector<double> colValues;

        for(int j = 0; j < numCols; j++) {
            double r = 0.00;

            if(isRandom) {
                r = this->getRandomNumber();
            }

            colValues.push_back(r);
        }

        this->values.push_back(colValues);
    }
}

Matrix Matrix::transpose()
{
    Matrix m(this->numCols, this->numRows, false);

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            m.setVal(j, i, this->getVal(i, j));
        }
    }

    return m;
}

Matrix Matrix::operator*(const Matrix &m2)
{
    if(this->numCols != m2.numRows){
        throw std::invalid_argument("The matrices have not the correct dimensions!");
    }

    Matrix product(this->numRows, m2.numCols, false);

    for(int r1 = 0; r1 < this->numRows; r1++) {  // loop through all rows of matrix 1
        for(int c2 = 0; c2 < m2.numCols; c2++) {  // loop through all columns of matrix 2
            double sum = 0.0;
            for(int i = 0; i < this->numCols; i++) {  // loop through all columns of matrix 1 and all rows of matrix 2 (at the same time)
                sum += (this->getVal(r1, i) * m2.getVal(i, c2));
            }
            product.setVal(r1, c2, sum);
        }
    }

    return product;
}

vector<double> Matrix::toVector()
{
    vector<double> vec;

    for(int r = 0; r < this->numRows; r++) {
        for(int c = 0; c < this->numCols; c++) {
            vec.push_back(this->getVal(r,c));
        }
    }

    return vec;
}

void Matrix::setVal(int r, int c, double v)
{
    this->values.at(r).at(c) = v;
}

void Matrix::printToConsole()
{
    for(int i = 0; i < this->numRows; i++) {
        for(int j = 0; j < this->numCols; j++) {
            std::cout << this->values.at(i).at(j) << "\t";
        }
        std::cout << "\n";
    }
}

double Matrix::getRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,1);

    return dis(gen);
}