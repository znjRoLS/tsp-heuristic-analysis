#pragma once

#include "matrix.h"

template<typename T>
class SquareMatrix: public Matrix<T> {
 public:
  SquareMatrix<T>(int n) : Matrix<T>(n, n) {}
};