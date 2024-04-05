#include "../../src/matrix/CSR.h"
#include <chrono>
#include <cmath>
#include <numbers>
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
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
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
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
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


void richardson(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double t, const double percision){
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

double max_eigenvalue(const CSR<double>& csr, const unsigned long int size, const double percision){
    std::vector<double> r(size, 1);
    double mu = 0, mu1 = 0, delta = 1e10, rr = 0;
    rr = std::sqrt(r * r);
    mu = (r * (csr * r)) / (rr * rr);
    while (delta > percision){
        r = csr * r;
        rr = std::sqrt(r * r);
        r = r * (1 / rr);
        mu1 = (r * (csr * r)) / (r * r);
        delta = std::abs(mu1 - mu);
        mu = mu1;
    }
    return mu;
}

std::vector<unsigned long int> redecorate(unsigned long int r){
    unsigned long int n = 2 << r;
    std::vector<unsigned long int> index(n, 0);
    index[2 << (r - 1)] = 1;
    unsigned long int step = 0;

    for (long unsigned int j = 2; j <= r; j++) {
        step = 2 << (r - j);
        for (unsigned long int k = 0; k < n; k += 2 * step) {
            index[k + step] = (2 << j) - index[k] - 1;
        }
    }

    return index;
}

const double pi = 3.14159265358979323846;
std::vector<double> find_tau(const unsigned long int r, const double lambda_max, const double lambda_min){
    unsigned long int n = 2 << r;
    std::vector<double> roots(n, 0);
    const double cos_n = std::cos(pi / static_cast<double>(n));
    const double sin_n = std::sin(pi / static_cast<double>(n));
    const double cos_2n = std::cos(pi / static_cast<double>(2 * n));
    double sin_i = std::sin(pi / static_cast<double>(2 * n));
    roots[0] = cos_2n;
    for(unsigned long int i = 1; i < n / 2 + 1; i++){
        roots[i] = roots[i - 1] * cos_n - sin_i * sin_n;
        sin_i = sin_i * cos_n + roots[i - 1] * sin_n;
        roots[n - i] = -roots[i - 1];
        roots[i - 1] = (lambda_min + lambda_max) / 2 + ((lambda_max - lambda_min) / 2) * roots[i - 1];
        roots[n - i] = (lambda_min + lambda_max) / 2 + ((lambda_max - lambda_min) / 2) * roots[n - i];
    }
    for (auto& it : roots){
        it = 1 / it;
    }
    return roots;
}

void chebyshev(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double lambda_max, const double lambda_min, unsigned long int r_, const double percision){
    std::ofstream timer, counter;
    timer.open("chebyshev_timer.txt");
    counter.open("chebyshev_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;
    
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  csr * x - b;
    double rr = std::sqrt(r * r);

    begin = std::chrono::high_resolution_clock::now();
    std::vector<unsigned long int> index = redecorate(r_);
    std::vector<double> tau = find_tau(r_, lambda_max, lambda_min);

    while (rr > percision){
        for (auto& it : index) {
            r = csr * x - b;
            x = x - tau[it] * r;
            rr = std::sqrt(r * r);

            end = std::chrono::high_resolution_clock::now();
            timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
            counter << rr << std::endl;
        }
    }

    timer.close();
    counter.close();
}

int main(){
    std::vector<double> val{1, 1, 2, 1, 4};
    std::vector<unsigned long int> col{0, 2, 1, 0, 2};
    std::vector<unsigned long int> row{0, 2, 3, 5};
    CSR<double> csr(val, col, row);
    std::vector<double> b{2, 4, 8}, x0{1, 1, 1};
    double percision = 1e-15, lambda_min, lambda_max;
    long unsigned int r_= 7;

    lambda_min = 0.69722436226800535344038936626475;
    lambda_max = max_eigenvalue(csr, r_, percision);
    const double t = 2 / (lambda_min + lambda_max);

    chebyshev(csr, b, x0, lambda_max, lambda_min, r_, percision);
    jacobi(csr, b, x0, percision);
    gauss_seidel(csr, b, x0, percision);
    richardson(csr, b, x0, t, percision);
    return 0;
}