#pragma once

#include "matrix/CSR.h"
#include <cmath>

template<typename T>
std::vector<double> chebSGS(const CSR<T>& csr, const std::vector<T>& b, const std::vector<T>& x0, const double ro = 0.9, const double percision = 1e-8){
    const std::size_t size = b.size();
    double mu0 = 1, mu1 = 1/ro, mu2 = 0;
    std::vector<double> y0 = x0, y1 = x0, y2 = x0;
    std::vector<double> r(size); 
    double storage = 0, central = 0;
    r = csr * y1 - b;
    double rr = std::sqrt(r * r);

    for (unsigned long int i = 0; i < size; i++){
        storage = 0;
        for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
            if (csr.get_cols()[j] != i){
                storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
            }
            else central = csr.get_values()[j];
        }
        y1[i] = (b[i] - storage) / central;
    }
    for (unsigned long int i = 0; i < size; i++){
        storage = 0;
        for (unsigned long int j = csr.get_rows()[size-i-1]; j < csr.get_rows()[size-i]; j++){
            if (csr.get_cols()[j] != size-i-1){
                storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
            }
            else central = csr.get_values()[j];
        }
        y1[size-i-1] = (b[size-i-1] - storage) / central;
    }
    r = csr * y1 - b;
    rr = std::sqrt(r * r);

    while (rr > percision){
        mu2 = 2 * mu1 / ro - mu0;

        for (unsigned long int i = 0; i < size; i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
                }
                else central = csr.get_values()[j];
            }
            y1[i] = (b[i] - storage) / central;
        }
        for (unsigned long int i = 0; i < size; i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[size-i-1]; j < csr.get_rows()[size-i]; j++){
                if (csr.get_cols()[j] != size-i-1){
                    storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
                }
                else central = csr.get_values()[j];
            }
            y1[size-i-1] = (b[size-i-1] - storage) / central;
        }

        y2 = (2 * mu1)/(ro * mu2) * y1 - (mu0 / mu2) * y0;

        r = csr * y2 - b;
        rr = std::sqrt(r * r);

        mu0 = mu1;
        mu1 = mu2;
        y0 = y1;
        y1 = y2;
    }

    return y2;
}