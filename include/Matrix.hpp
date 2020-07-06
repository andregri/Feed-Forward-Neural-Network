#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Matrix
{
public:
    Matrix(int numRows, int numCols, bool isRandom);

    Matrix transpose();
    Matrix operator*(const Matrix&);
    vector<double> toVector();

    void setVal(int r, int c, double v);
    double getVal(int r, int c) const {return this->values.at(r).at(c);}

    void printToConsole();

    int getNumRows() {return this->numRows;}
    int getNumCols() {return this->numCols;}

private:
    int numRows;
    int numCols;
    vector<vector<double>> values;

    double getRandomNumber();
};

#endif //_MATRIX_HPP_