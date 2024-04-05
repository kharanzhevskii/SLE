#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> richardson(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double t, const double percision){
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r = csr * x - b;
    double rr = std::sqrt(r * r);

    while (rr > percision){
        r = csr * x - b;
        x = x - t * r;
        rr = std::sqrt(r * r);
    }
    
    return x;
}