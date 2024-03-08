#include "../../src/matrix/CSR.h"
#include <chrono>
#include <cmath>
#include <fstream>


void gauss_seidel(const CSR<double>& csr, const std::vector<double>& b,const std::vector<double>& x0, const double percision){
    std::ofstream timer, counter;
    timer.open("gauss-seidel_timer.txt");
    counter.open("gauss-seidel_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;
    
    std::vector<double> x = x0;
    std::vector<double> r(b.size()); 
    double storage = 0;
    r =  b - csr * x;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        for (std::vector<double>::size_type i = 0; i < b.size(); i++){
            storage = 0;
            for (int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * x[csr.get_cols()[j]];
                }
            }
            x[i] = (b[i] - storage) / csr(i,i);
        }
        r = b - csr * x;
        rr = std::sqrt(r * r);

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }

    timer.close();
    counter.close();
}


void jacobi(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision){
    std::ofstream timer, counter;
    timer.open("jacobi_timer.txt");
    counter.open("jacobi_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;

    std::vector<double> x = x0;
    std::vector<double> x_next(b.size());
    std::vector<double> r(b.size());
    double storage = 0;
    r =  b - csr * x;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        for (std::vector<double>::size_type i = 0; i < b.size(); i++){
            storage = 0;
            for (int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * x[csr.get_cols()[j]];
                }
            }
            x_next[i] = (b[i] - storage) / csr(i,i);
        }
        x = x_next;
        r = b - csr * x;
        rr = std::sqrt(r * r);

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }
    
    timer.close();
    counter.close();
}  


void richardson(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision, const double t){
    std::ofstream timer, counter;
    timer.open("richardson_timer.txt");
    counter.open("richardson_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;
    
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  b - csr * x;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        x = x - t * (csr * x - b);
        r = b - csr * x;
        rr = std::sqrt(r * r);

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }
    
    timer.close();
    counter.close();
}

int main(){
    std::vector<double> val{10, 4, 20, 1, 1, 4, 20, 1, 2, 10};
    std::vector<int> col{0, 2, 1, 2, 0, 1, 2, 3, 2, 3};
    std::vector<int> row{0, 2, 4, 8, 10};
    CSR<double> csr(val, col, row);
    std::vector<double> b{8, 12, 4, 2}, x0{1, 1, 1, 1};
    const double percision = 1e-15;
    const double t = 0.063147;

    jacobi(csr, b, x0, percision);
    gauss_seidel(csr, b, x0, percision);
    richardson(csr, b, x0, percision, t);
    return 0;
}