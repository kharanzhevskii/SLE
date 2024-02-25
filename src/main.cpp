#include <stdlib.h>
#include <fstream>
#include <string>
#include "matrix/CSR.h"
#include "matrix/dense.h"

int main(int argc, char** argv){
    std::vector<double> val{1, 2, 3, 4, 1, 11};
    std::vector<int> col{0, 1, 3, 2, 1, 3};
    std::vector<int> row{0, 3, 4, 6};
    std::vector<double> vald{1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
    int c = 3, r = 4;
    CSR<double> csr(val, col, row);
    Dense<double> dense(vald, c, r);
    std::vector<double> mul{1, 2, 3, 4};
    std::vector<double> one, two;
    one = csr * mul;
    two = dense * mul;
    std::cout << csr << dense << one << two;
    return 0;
}