#include "../include/Matrix.hpp"

Matrix *Matrix::transpose() {
    Matrix *m = new Matrix(numCols, numRows, false);

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            m->setValue(j, i, this->getValue(i,j));
        }
    }

    return m;
}

Matrix *Matrix::copy() {
    Matrix *m = new Matrix(numRows, numCols, false);

    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            m->setValue(i, j, this->getValue(i,j));
        }
    }

    return m;
}

Matrix::Matrix(int numRows, int numCOls, bool isRandom) {
    this->numRows = numRows;
    this->numCols = numCols;

    for(int i = 0; i < numRows; i++) {
        vector<double> colValues;

        for(int j = 0; j < numCols; j++) {
            double r = isRandom == true ? generateRandomNumber() : 0;

            colValues.push_back(r);
        }

        this->values.push_back(colValues);
    }
}

double Matrix::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-.0001, .0001);

    return dis(gen);
}

void Matrix::printToConsole() {
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            cout << this->values.at(i).at(j) << "\t\t";
        }
        cout << '\n';
    }

}