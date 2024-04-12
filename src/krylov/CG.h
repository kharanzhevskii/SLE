#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> CG(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double percision = 1e-8){
    std::vector<double> x = x0;
    std::vector<double> r(b.size()), d(b.size()), r1(b.size()); 
    double alpha = 0, betta = 0, storage = 0;
    r = csr * x - b;
    d = r;
    double rr = std::sqrt(r * r);

    while (rr > percision){
        alpha = (r * r) / (d * (csr * d));
        x = x - alpha * d;
        r1 = csr * x - b;
        storage = (r1 * r1);
        rr = std::sqrt(storage);
        if (rr <= percision) break;
        betta = storage / (r * r);
        d = r1 + betta * d;
        r = r1;
    }

    return x;
}