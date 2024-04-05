#include "../../src/matrix/CSR.h"
#include "../../src/matrix/elliptic.h"
#include <chrono>
#include <cmath>
#include <numbers>
#include <fstream>


void gauss_seidel(const CSR<double>& csr, const std::vector<double>& b,const std::vector<double>& x0, const double percision){
    std::cout << "started" << std::endl;
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
    std::cout << "ended" << std::endl;
}


void jacobi(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision){
    std::cout << "started" << std::endl;
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
    std::cout << "ended" << std::endl;
}  


void richardson(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision, const double t){
    std::cout << "started" << std::endl;
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
    std::cout << "ended" << std::endl;
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
    std::cout << "started" << std::endl;
    std::ofstream timer, counter;
    std::string timerstr = std::to_string(r_) + "_chebyshev_timer.txt";
    std::string counterstr = std::to_string(r_) + "_chebyshev_counter.txt";
    timer.open(timerstr);
    counter.open(counterstr);
    std::chrono::high_resolution_clock::time_point begin, end;
    
    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  csr * x - b;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

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
    std::cout << "ended" << std::endl;
}

void FGD(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision){
    std::cout << "started" << std::endl;
    std::ofstream timer, counter;
    timer.open("FGD_timer.txt");
    counter.open("FGD_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;

    std::vector<double> x = x0;
    std::vector<double> r(b.size());

    r = csr * x - b;
    double rr = std::sqrt(r * r);
    double t = (r * r) / (r * (csr * r));
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        x = x - t * r;
        r = csr * x - b;
        rr = std::sqrt(r * r);
        t = (r * r) / (r * (csr * r));

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }
    
    timer.close();
    counter.close();
    std::cout << "ended" << std::endl;
}

void richardson_improved(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision){
    std::cout << "started" << std::endl;
    std::ofstream timer, counter;
    timer.open("richardson_improved_timer.txt");
    counter.open("richardson_improved_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;

    std::vector<double> x = x0;
    std::vector<double> r(b.size());
    r =  csr * x - b;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    double t = max_eigenvalue(csr, b.size(), percision);
    t = 1 / t;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        r = csr * x - b;
        x = x - t * r;
        rr = std::sqrt(r * r);

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }

    timer.close();
    counter.close();
    std::cout << "ended" << std::endl;
}

void SGS(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double percision){
    std::cout << "started" << std::endl;
    std::ofstream timer, counter;
    timer.open("SGS_timer.txt");
    counter.open("SGS_counter.txt");
    std::chrono::high_resolution_clock::time_point begin, end;

    std::vector<double> x = x0;
    std::vector<double> r(b.size()); 
    double storage = 0;
    r = csr * x - b;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    while (rr > percision){
        for (unsigned long int i = 0; i < b.size(); i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * x[csr.get_cols()[j]];
                }
            }
            x[i] = (b[i] - storage) / csr(i,i);
        }
        for (unsigned long int i = 0; i < b.size(); i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[b.size()-i-1]; j < csr.get_rows()[b.size()-i]; j++){
                if (csr.get_cols()[j] != b.size()-i-1){
                    storage += csr.get_values()[j] * x[csr.get_cols()[j]];
                }
            }
            x[b.size()-i-1] = (b[b.size()-i-1] - storage) / csr(b.size()-i-1, b.size()-i-1);
        }
        r = csr * x - b;
        rr = std::sqrt(r * r);

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }

    timer.close();
    counter.close();
    std::cout << "ended" << std::endl;
}

void chebSGS(const CSR<double>& csr, const std::vector<double>& b, const std::vector<double>& x0, const double ro = 0.9, const double percision = 1e-8){
    std::cout << "started" << std::endl;
    std::ofstream timer, counter;
    std::string timerstr = std::to_string(ro) + "_chebSGS_timer.txt";
    std::string counterstr = std::to_string(ro) + "_chebSGS_counter.txt";
    timer.open(timerstr);
    counter.open(counterstr);
    std::chrono::high_resolution_clock::time_point begin, end;

    const std::size_t size = b.size();
    double mu0 = 1, mu1 = 1/ro, mu2 = 0;
    std::vector<double> y0 = x0, y1 = x0, y2 = x0;
    std::vector<double> r(size); 
    double storage = 0, central = 0;
    r = csr * y1 - b;
    double rr = std::sqrt(r * r);
    counter << rr << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    for (unsigned long int i = 0; i < size; i++){
        storage = 0;
        for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
            if (csr.get_cols()[j] != i){
                storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
            }
            else central = csr.get_values()[j];
        }
        y1[i] = (b[i] - storage) / central;
    }
    for (unsigned long int i = 0; i < size; i++){
        storage = 0;
        for (unsigned long int j = csr.get_rows()[size-i-1]; j < csr.get_rows()[size-i]; j++){
            if (csr.get_cols()[j] != size-i-1){
                storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
            }
            else central = csr.get_values()[j];
        }
        y1[size-i-1] = (b[size-i-1] - storage) / central;
    }
    r = csr * y1 - b;
    rr = std::sqrt(r * r);

    while (rr > percision){
        mu2 = 2 * mu1 / ro - mu0;

        for (unsigned long int i = 0; i < size; i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[i]; j < csr.get_rows()[i+1]; j++){
                if (csr.get_cols()[j] != i){
                    storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
                }
                else central = csr.get_values()[j];
            }
            y1[i] = (b[i] - storage) / central;
        }
        for (unsigned long int i = 0; i < size; i++){
            storage = 0;
            for (unsigned long int j = csr.get_rows()[size-i-1]; j < csr.get_rows()[size-i]; j++){
                if (csr.get_cols()[j] != size-i-1){
                    storage += csr.get_values()[j] * y1[csr.get_cols()[j]];
                }
                else central = csr.get_values()[j];
            }
            y1[size-i-1] = (b[size-i-1] - storage) / central;
        }

        y2 = (2 * mu1)/(ro * mu2) * y1 - (mu0 / mu2) * y0;

        r = csr * y2 - b;
        rr = std::sqrt(r * r);

        mu0 = mu1;
        mu1 = mu2;
        y0 = y1;
        y1 = y2;

        end = std::chrono::high_resolution_clock::now();
        timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        counter << rr << std::endl;
    }

    timer.close();
    counter.close();
    std::cout << "ended" << std::endl;
}

int main(){
    CSR<double> csr = elliptic(64, 1.0, 5.0);
    std::vector<double> b(4096, 2), x0(4096, 1);
    double percision = 1e-12, lambda_min, lambda_max, ro_1 = 0.9, ro_2 = 0.95;
    long unsigned int r_1 = 7, r_2 = 15;

    std::vector<double> eigenvalues = elleptic_eigenvalues(64, 1.0, 5.0);
    lambda_min = eigenvalues[0];
    lambda_max = eigenvalues[eigenvalues.size()-1];

    const double t = 2 / (lambda_min + lambda_max);

    chebyshev(csr, b, x0, lambda_max, lambda_min, r_1, percision);
    chebyshev(csr, b, x0, lambda_max, lambda_min, r_2, percision);
    jacobi(csr, b, x0, percision);
    gauss_seidel(csr, b, x0, percision);
    richardson(csr, b, x0, percision, t);
    chebSGS(csr, b, x0, ro_1, percision);
    chebSGS(csr, b, x0, ro_2, percision);
    SGS(csr, b, x0, percision);
    richardson_improved(csr, b, x0, percision);
    FGD(csr, b, x0, percision);

    return 0;
}