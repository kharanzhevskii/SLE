#pragma once

#include "matrix/CSR.h"
#include "chebyshev/max_eigenvalue.h"
#include <cmath>

template<typename T>
std::vector<double> richardson_improved(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double percision){
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  csr * x - b;
    double rr = std::sqrt(r * r);

    double t = max_eigenvalue(csr, b.size(), percision);
    t = 1 / t;

    while (rr > percision){
        r = csr * x - b;
        x = x - t * r;
        rr = std::sqrt(r * r);
    }
    
    return x;
}