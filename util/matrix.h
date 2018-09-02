#ifndef TSPHEURISTICANALYSIS_MATRIX_H
#define TSPHEURISTICANALYSIS_MATRIX_H

#include <vector>

using std::vector;

template<typename T>
class Matrix {
public:
    Matrix(int n, int m);

    vector<T>& operator[](int i);

private:
    vector<vector<T>> data_;
};

#include "matrix.cc"

#endif //TSPHEURISTICANALYSIS_MATRIX_H
