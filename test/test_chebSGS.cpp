#include "gtest/gtest.h"
#include "chebyshev/chebSGS.h"
#include "matrix/elliptic.h"


TEST(chebSGS, Test1){
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, ans{0, 2, 2}, res(3, 0), x0{1, 1, 1};
    const double percision = 1e-10;
    const double ro = 0.9;
    res = chebSGS(csr, b, x0, ro, percision);
    for (unsigned long int i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-9);
    }
}

TEST(chebSGS, Test2){
    CSR<double> csr = elliptic(32, 1.0, 5.0);
    std::vector<double> b(1024, 0), ans(1024, 0), res(1024, 0), x0(1024, 1);
    const double percision = 1e-8;
    const double ro = 0.95;
    res = chebSGS(csr, b, x0, ro, percision);
    for (unsigned long int i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-7);
    }
}