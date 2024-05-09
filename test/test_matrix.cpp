#include <gtest/gtest.h>
#include "matrix/CSR.h"
#include "matrix/dense.h"

TEST(Test, TestCSR) {
    std::vector<double> val{1, 2, 3, 4, 1, 11};
    std::vector<unsigned long int> col{0, 1, 3, 2, 1, 3};
    std::vector<unsigned long int> row{0, 3, 4, 6};
    CSR<double> csr(val, col, row);
    std::vector<double> mul{1, 2, 3, 4}, ans{17, 12, 46}, res(3, 0);
    res = csr * mul;
    for (unsigned long int i = 0; i < 3; i++){
        ASSERT_NEAR(res[i], ans[i], 1e-12);
    }
    std::cout << csr;
}

TEST(Test, TestDense) {
    std::vector<double> vald{1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
    unsigned long int c = 3, r = 4;
    Dense<double> dense(vald, c, r);
    std::vector<double> mul{1, 2, 3, 4}, ans{17, 12, 46}, res(3, 0);
    res = dense * mul;
    for (unsigned long int i = 0; i < 3; i++){
        ASSERT_NEAR(res[i], ans[i], 1e-12);
    }
    std::cout << dense;
}

TEST(Test, TestVector) {
    std::vector<float> one{1, 2, 3}, two{1, 1, 1}, three{0, 4, 0}, four(3);
    two = three - one;
    four = 0.2f * (one * 2.5f);
    std::cout << four << two;
    float dot_product = four * two;
    ASSERT_NEAR(dot_product, -3, 1e-12);
    std::cout << three << one;
}