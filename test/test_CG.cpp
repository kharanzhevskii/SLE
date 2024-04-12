#include "gtest/gtest.h"
#include "krylov/CG.h"
#include "matrix/elliptic.h"


TEST(CG, Test1){
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, ans{0, 2, 2}, res(3, 0), x0{1, 1, 1};
    const double percision = 1e-10;
    res = CG(csr, b, x0, percision);
    for (unsigned long int i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-9);
    }
}

TEST(CG, Test2){
    const unsigned long int L = 256;
    const unsigned long int N = L * L;
    CSR<double> csr = elliptic(L, 1.0, 5.0);
    std::vector<double> b(N, 0), ans(N, 0), res(N, 0), x0(N, 1);
    const double percision = 1e-8;
    res = CG(csr, b, x0, percision);
    for (unsigned long int i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-7);
    }
}