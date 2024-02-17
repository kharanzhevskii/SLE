#include "tridiagonal.h"

std::vector<double> tridiagonal(const std::vector<double>& A, int n){
    std::vector<double> p(n);
    std::vector<double> q(n);
    std::vector<double> x(n+1);
    p[0] = -A[2*n+1] / A[n];
    q[0] = A[3*n+1] / A[n];
    for (int j = 0; j < n-1; j++){
        p[j+1] = -A[2*n+2+j]/(A[j] * p[j] + A[n+1+j]);
        q[j+1] = (A[3*n+2+j] - A[j] * q[j]) / (A[j] * p[j] + A[n+1+j]);
    }
    x[n] = (A[4*n+1] - A[n-1] * q[n-1]) / (A[n-1] * p[n-1] + A[2*n]);
    for (int i = n-1; i >= 0; i--){
        x[i] = p[i] * x[i+1] + q[i];
    }
    return x;
}