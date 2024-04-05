#pragma once

#include "matrix/CSR.h"
#include <cmath>

template <typename T>
double max_eigenvalue(const CSR<T>& csr, const unsigned long int size, const double percision){
    std::vector<double> r(size, 1);
    double mu = 0, mu1 = 0, delta = 1e10, rr = 0;
    rr = std::sqrt(r * r);
    mu = (r * (csr * r)) / (rr * rr);
    while (delta > percision){
        r = csr * r;
        rr = std::sqrt(r * r);
        r = r * (1 / rr);
        mu1 = (r * (csr * r)) / (r * r);
        delta = std::abs(mu1 - mu);
        mu = mu1;
    }
    return mu;
}

