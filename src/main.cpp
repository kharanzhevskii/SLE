#include "matrix/elliptic.h"

int main(){
    std::cout.precision(16);
    CSR one = elliptic(2, 1, 5);
    CSR two = elliptic(3, 1, 5);
    std::vector<double> lambda1 = elleptic_eigenvalues(2, 1, 5);
    std::vector<double> lambda2 = elleptic_eigenvalues(3, 1, 5);
    double chi1 = elleptic_chi2(2, 1, 5);
    double chi2 = elleptic_chi2(3, 1, 5);
    std::cout << one << std::endl;
    std::cout << two << std::endl;
    std::cout << lambda1 << std::endl;
    std::cout << lambda2 << std::endl;
    std::cout << chi1 << std::endl;
    std::cout << chi2 << std::endl;
    return 0;
}