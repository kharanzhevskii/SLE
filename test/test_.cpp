#include <gtest/gtest.h>
#include "tridiagonal.h"
#include <iostream>

TEST(Test, Test1) {
    std::vector<double> A{2, 2, 2, 1, 2, 3, 4, 4, 4, 4, 5, 4, 7, 8};
    std::vector<double> x = tridiagonal(A, 3);
    std::vector<double> ans{4.428571428571429, 0.142857142857142, -1.285714285714285, 2.642857142857143};
    for (int i = 0; i < 4; i++){
        ASSERT_NEAR(x[i], ans[i], 1e-10);
        //std::cout << x[i] << " " << ans[i] << std::endl;
    }
}

TEST(Test, Test2) {
    std::vector<double> A{2, 2, 3, 3, 1, 2, 3, 2, 1, 4, 4, 4, 8, 6, 5, 4, 3, 7};
    std::vector<double> x = tridiagonal(A, 4);
    std::vector<double> ans{5.6894409937888195, 0.0776397515527950, -1.6335403726708075, 2.186335403726708, 0.440993788819876};
    for (int i = 0; i < 5; i++){
        ASSERT_NEAR(x[i], ans[i], 1e-10);
        //std::cout << x[i] << " " <<  ans[i] << std::endl;
    }
}