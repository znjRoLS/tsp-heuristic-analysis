#ifndef TSPHEURISTICANALYSIS_MATRIX_H
#define TSPHEURISTICANALYSIS_MATRIX_H

#include <vector>

using std::vector;

template<typename T>
class Matrix {
public:
    Matrix(int n, int m);
    Matrix(vector<vector<T>> data);

    vector<T>& operator[](int i);

private:
    const int n_;
    const int m_;
    vector<vector<T>> data_;
};

#include "matrix.cc"

#endif //TSPHEURISTICANALYSIS_MATRIX_H
