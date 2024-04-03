#pragma once

#include "CSR.h"
#include <cmath>
#include <numbers>
#include <algorithm>


template<typename T>
CSR<T> elliptic(const unsigned long int L, const T a, const T b){
    const unsigned long int N = L * L;
    std::vector<T> values;
    std::vector<unsigned long int> cols, rows;
    const T bb = 2 * b;

    values.push_back(bb);
    values.push_back(a);
    values.push_back(a);
    cols.push_back(0);
    cols.push_back(1);
    cols.push_back(L);
    rows.push_back(0);
    unsigned long int num_of_elements = 3;
    rows.push_back(num_of_elements);

    for (unsigned long int i = 0; i < L-1; i++){
        values.push_back(a);
        values.push_back(bb);
        values.push_back(a);
        values.push_back(a);
        cols.push_back(0+i);
        cols.push_back(1+i);
        cols.push_back(2+i);
        cols.push_back(L+1+i);
        num_of_elements += 4;
        rows.push_back(num_of_elements);    
    }

    for (unsigned long int i = 0; i < N-2*L; i++){
        values.push_back(a);
        values.push_back(a);
        values.push_back(bb);
        values.push_back(a);
        values.push_back(a);
        cols.push_back(0+i);
        cols.push_back(L-1+i);
        cols.push_back(L+i);
        cols.push_back(L+1+i);
        cols.push_back(2*L+i);
        num_of_elements += 5;
        rows.push_back(num_of_elements);    
    }

    for (unsigned long int i = 0; i < L-1; i++){
        values.push_back(a);
        values.push_back(a);
        values.push_back(bb);
        values.push_back(a);
        cols.push_back(N-2*L+i);
        cols.push_back(N-L-1+i);
        cols.push_back(N-L+i);
        cols.push_back(N-L+1+i);
        num_of_elements += 4;
        rows.push_back(num_of_elements);    
    }

    values.push_back(a);
    values.push_back(a);
    values.push_back(bb);
    cols.push_back(N-L-1);
    cols.push_back(N-2);
    cols.push_back(N-1);
    num_of_elements += 3;
    rows.push_back(num_of_elements);

    CSR res(values, cols, rows);
    return res;
}

template<typename T>
std::vector<double> elleptic_eigenvalues(const unsigned long int L, const T a_, const T b_){
    const double a = static_cast<double>(a_);
    const double b = static_cast<double>(b_);

    const unsigned long int N = L * L;
    std::vector<double> roots(L, 0);
    std::vector<double> res;

    const double cos_1 = std::cos(std::numbers::pi_v<double> / static_cast<double>(L+1));
    const double sin_1 = std::sin(std::numbers::pi_v<double> / static_cast<double>(L+1));
    const double cos_2 = cos_1 * cos_1 - sin_1 * sin_1;
    double sin_i = 2 * sin_1 * cos_1;
    roots[0] = cos_1;
    roots[1] = cos_2;

    for (unsigned long int i = 2; i <= L-1; i++){
        roots[i] = roots[i-1] * cos_1 - sin_i * sin_1;
        sin_i = sin_i * cos_1 + roots[i-1] * sin_1;
    }
    
    double tmp = 0;
    for (unsigned long int k = 0; k <= L-1; k++){
        tmp = 2 * b + 2 * a * roots[k];
        for (unsigned long int m = 0; m <= L-1; m++){
            res.push_back(tmp + 2*a*roots[m]);
        }
    }

    std::sort(res.begin(), res.end());
    return res;
}

template<typename T>
double elleptic_chi2(const unsigned long int L, const T a_, const T b_){
    const double a = static_cast<double>(a_);
    const double b = static_cast<double>(b_);

    const double cos_1 = std::cos(std::numbers::pi_v<double> / static_cast<double>(L+1));
    const double c = 2 * std::abs(a) * cos_1;
    const double chi2 = (b + c) / (b - c);
    return chi2;
}