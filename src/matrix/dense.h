#pragma once
#include "vector.h"

template<typename T>
class Dense {
private:
    std::vector<T> values;
    int cols;
    int rows;

public:
    Dense (const std::vector<T>& values, int cols, int rows):
        values(values), cols(cols), rows(rows) {}
    
    const std::vector<T> get_values() const{
        return values;
    }
    const int get_cols() const{
        return cols;
    }
    const int get_rows() const{
        return rows;
    }

    Dense (const Dense<T>& m): values(m.get_values()), cols(m.get_cols()), rows(m.get_rows()) {}
    ~Dense() {}

    T operator()(int i, int j) const {
        return values[rows * i + j];
    }
};

template<typename T>
std::vector<T> operator*(const Dense<T>& dense, const std::vector<T>& v) {
    std::vector<T> res(dense.get_cols());
    for (int i = 0; i < dense.get_cols(); i++) {
        for (int j = 0; j < dense.get_rows(); j++){
            res[i] += dense[dense.get_rows() * i + j] * v[j];
        }
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Dense<T>& dense) {
    const std::vector<T> values = csr.get_values();
    int cols = dense.get_cols();
    int rows = dense.get_rows();
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            std::cout << values[rows * i + j] << ' ';
        }
        std:: cout << std::endl;
    }
    return os;
}