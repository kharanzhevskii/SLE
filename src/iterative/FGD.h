#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> FGD(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double percision){
    std::vector<double> x = x0;
    std::vector<double> r(b.size());

    r = csr * x - b;
    double rr = std::sqrt(r * r);
    double t = (r * r) / (r * (csr * r));

    while (rr > percision){
        x = x - t * r;
        r = csr * x - b;
        rr = std::sqrt(r * r);
        t = (r * r) / (r * (csr * r));
    }
    
    return x;
}