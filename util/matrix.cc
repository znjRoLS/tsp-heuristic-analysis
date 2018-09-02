
template<typename T>
Matrix<T>::Matrix(int n, int m):
    data_(n, vector<T>(m))
{

}

template<typename T>
vector<T>& Matrix<T>::operator[](int i) {
    return data_[i];
}