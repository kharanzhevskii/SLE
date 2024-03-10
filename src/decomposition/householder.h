#pragma once

#include"matrix/dense.h"
#include <cmath>

template<typename T>
std::pair<DenseMatrix<double>, DenseMatrix<double>> householder(const Dense<T>& dense){
    std::vector<T> values = dense.get_values();
    int height = dense.get_height();
    int width = dense.get_width();
    Dense<double> R(values, height, width);     // first R = A
    std::vector<double> q(height * height, 0);
    for (int i = 0; i < height; i++){
        q[i * width + i] = 1;
    }
    Dense<double> Q(q, height, height);     // first Q = I

}