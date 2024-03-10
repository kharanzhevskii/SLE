#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> richardson(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double percision, const double t){
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  b - csr * x;
    double rr = std::sqrt(r * r);

    while (rr > percision){
        r = csr * x - b;
        x = x - t * r;
        rr = std::sqrt(r * r);
    }
    
    return x;
}