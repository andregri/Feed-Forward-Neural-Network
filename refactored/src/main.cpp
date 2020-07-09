#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>
#include "../include/utils/Math.hpp"
#include "../include/Matrix.hpp"

using namespace std;

int main(int argc, char **argv) {
    for(int i = 0; i < 10000; i++) {
        Matrix *a = new Matrix(100, 100, true);
        Matrix *b = new Matrix(100, 100, true);

        Matrix *c = new Matrix(a->getNumCols(), b->getNumRows(), false);
        cout << "Multiply matrix at index " << i << "\n";
        utils::Math::multiplyMatrix(a, b, c);
    }

    return 0;
}