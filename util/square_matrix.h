#pragma once

#include "matrix.h"

template<typename T>
class SquareMatrix : public Matrix<T> {
 public:
  SquareMatrix<T>(int n);
  SquareMatrix<T>(vector<vector<T>> data);
};

template<typename T>
SquareMatrix<T>::SquareMatrix(int n):
    Matrix<T>(n, n) {}

template<typename T>
SquareMatrix<T>::SquareMatrix(vector<vector<T>> data) :
    Matrix<T>(data) {}