#pragma once
#include "matrix/CSR.h"
#include "max_eigenvalue.h"
#include <cmath>
#include <numbers>


std::vector<unsigned long int> redecorate(unsigned long int r){
    unsigned long int n = 2 << r;
    std::vector<unsigned long int> index(n, 0);
    index[2 << (r - 1)] = 1;
    unsigned long int step = 0;

    for (long unsigned int j = 2; j <= r; j++) {
        step = 2 << (r - j);
        for (unsigned long int k = 0; k < n; k += 2 * step) {
            index[k + step] = (2 << j) - index[k] - 1;
        }
    }

    return index;
}


std::vector<double> find_tau(const unsigned long int r, const double lambda_max, const double lambda_min){
    unsigned long int n = 2 << r;
    std::vector<double> roots(n, 0);
    const double cos_n = std::cos(std::numbers::pi / static_cast<double>(n));
    const double sin_n = std::sin(std::numbers::pi / static_cast<double>(n));
    const double cos_2n = std::cos(std::numbers::pi / static_cast<double>(2 * n));
    double sin_i = std::sin(std::numbers::pi / static_cast<double>(2 * n));
    roots[0] = cos_2n;
    for(unsigned long int i = 1; i < n / 2 + 1; i++){
        roots[i] = roots[i - 1] * cos_n - sin_i * sin_n;
        sin_i = sin_i * cos_n + roots[i - 1] * sin_n;
        roots[n - i] = -roots[i - 1];
        roots[i - 1] = (lambda_min + lambda_max) / 2 + ((lambda_max - lambda_min) / 2) * roots[i - 1];
        roots[n - i] = (lambda_min + lambda_max) / 2 + ((lambda_max - lambda_min) / 2) * roots[n - i];
    }
    for (auto& it : roots){
        it = 1 / it;
    }
    return roots;
}

template <typename T>
std::vector<double> chebyshev(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double lambda_max, const double lambda_min, unsigned long int r_, const double percision){
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  csr * x - b;
    double rr = std::sqrt(r * r);

    std::vector<unsigned long int> index = redecorate(r_);
    std::vector<double> tau = find_tau(r_, lambda_max, lambda_min);

    while (rr > percision){
        for (auto& it : index) {
            r = csr * x - b;
            x = x - tau[it] * r;
            rr = std::sqrt(r * r);
        }
    }

    return x;
}

