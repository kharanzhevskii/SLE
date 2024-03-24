// #include <stdlib.h>
// #include <fstream>
// #include <string>
#include "matrix/CSR.h"
#include "iterative/richardson.h"
#include "chebyshev/max_eigenvalue.h"
#include <iostream>

int main(int argc, char** argv){
    std::vector<double> val{59, 7, 91, 6, 83, 6, 59};
    std::vector<unsigned long int> col{0, 2, 1, 1, 2, 2, 3};
    std::vector<unsigned long int> row{0, 2, 3, 5, 7};
    // std::vector<double> vald{1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
    // int c = 3, r = 4;
    CSR<double> csr(val, col, row);
    // Dense<double> dense(vald, c, r);
    std::vector<double> b{1, 1, 1, 1}, x0{0, 0, 0, 0};
    // std::vector<double> one, two;
    double lambda_max = max_eigenvalue(csr, 4, 1e-16);
    std:: cout << lambda_max;
    double tau = 2 / lambda_max;
    std::vector<double> ans = richardson(csr, b, x0, 1e-12, tau);
    std::cout << ans;
    return 0;
}