#include "gtest/gtest.h"
#include "iterative/richardson.h"
#include "iterative/richardson_improved.h"


TEST(Richardson, Richardson) {
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, ans{0, 2, 2}, res(3, 0), x0{1, 1, 1};
    const double percision = 1e-10;
    const double t = 0.4;
    res = richardson(csr, b, x0, t, percision);
    for (std::size_t i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-9);
    }
}

TEST(Richardson, RichardsonImproved) {
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, ans{0, 2, 2}, res(3, 0), x0{1, 1, 1};
    const double percision = 1e-10;
    res = richardson_improved(csr, b, x0, percision);
    for (std::size_t i = 0; i < res.size(); i++){
        ASSERT_NEAR(res[i], ans[i], 1e-9);
    }
}