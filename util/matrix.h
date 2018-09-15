#pragma once

#include <vector>

using std::vector;
using std::pair;

template<typename T>
class Matrix {
 public:
  Matrix(int n, int m);

  Matrix(vector<vector<T>> data);

  vector<T> &operator[](int i);

  pair<int, int> size();

 private:
  const int n_;
  const int m_;
  vector<vector<T>> data_;
};

template<typename T>
Matrix<T>::Matrix(int n, int m):
    n_(n),
    m_(m),
    data_(n, vector<T>(m)) {

}

template<typename T>
Matrix<T>::Matrix(vector<vector<T>> data):
    n_(data.size()),
    m_(data[0].size()),
    data_(data) {

}

template<typename T>
vector<T> &Matrix<T>::operator[](int i) {
  return data_[i];
}

template<typename T>
pair<int, int> Matrix<T>::size() {
  return {n_, m_};
}
