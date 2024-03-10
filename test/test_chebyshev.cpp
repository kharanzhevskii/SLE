#include "gtest/gtest.h"
#include "chebyshev/chebyshev.h"

TEST(Chebyshev, Test1) {
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, ans{0, 2, 2}, res(3, 0), x0{1, 1, 1};
    double percision = 1e-10, lambda_min, lambda_max;
    long unsigned int r_= 7;

    lambda_min = 0.69722436226800535344038936626475;
    lambda_max = max_eigenvalue(csr, r_, percision);

    res = chebyshev(csr, b, x0, lambda_max, lambda_min, r_, percision);

    ASSERT_NEAR(lambda_max, 4.3027756377, 1e-9);
    for (std::size_t i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-9);
    }
}