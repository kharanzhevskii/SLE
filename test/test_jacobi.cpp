#include "gtest/gtest.h"
#include "iterative/jacobi.h"


TEST(Jacobi, Test1) {
    std::vector<double> val{10, 4, 20, 1, 1, 4, 20, 1, 2, 10};
    std::vector<int> col{0, 2, 1, 2, 0, 1, 2, 3, 2, 3};
    std::vector<int> row{0, 2, 4, 8, 10};
    CSR<double> csr(val, col, row);
    std::vector<double> b{8, 12, 4, 2}, ans{0.7875, 0.5984375, 0.03125, 0.19375}, res(4, 0), x0{1, 1, 1, 1};
    const double percision = 1e-10;
    res = jacobi(csr, b, x0, percision);
    for (std::size_t i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-8);
    }
}