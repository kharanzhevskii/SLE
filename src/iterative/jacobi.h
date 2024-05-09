#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> jacobi(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double percision){
    std::vector<double> x = x0;
    std::vector<double> x_next(b.size());
    std::vector<double> r(b.size());
    double storage = 0, central = 0;
    r = csr * x - b;
    double rr = std::sqrt(r * r);

    while (rr > percision){
        for (unsigned long int i = 0; i < b.size(); i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * x[csr.get_cols()[j]];
                }
                else central = csr.get_values()[j];
            }
            x_next[i] = (b[i] - storage) / central;
        }
        x = x_next;
        r = b - csr * x;
        rr = std::sqrt(r * r);
    }
    
    return x;
}        