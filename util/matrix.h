#ifndef TSPHEURISTICANALYSIS_MATRIX_H
#define TSPHEURISTICANALYSIS_MATRIX_H

#include <vector>

using std::vector;

template<typename T>
class Matrix {
public:
    Matrix(int n, int m);

private:
    vector<vector<T>> data_;
};

#include "matrix.cpp"

#endif //TSPHEURISTICANALYSIS_MATRIX_H
