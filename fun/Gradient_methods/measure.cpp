#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <fstream>
#include <chrono>
#include "../../src/matrix/elliptic.h"
#include <cmath>

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}


int main(){
    const double percision = 1e-8;
    unsigned long int N = 0;
    std::ofstream timer, counter;
    std::string timerstr = "CG_time.txt";
    std::string counterstr = "CG_memory.txt";
    timer.open(timerstr);
    counter.open(counterstr);
    std::chrono::high_resolution_clock::time_point begin, end;

    for (unsigned long int L = 64; L < 256; L+=2){
    N = L * L;
    CSR<double> csr = elliptic(L, 1.0, 5.0);
    std::vector<double> b(N, 0), x0(N, 1);

    std::cout << "started" << std::endl;
    
    //int PhysMemUsed = 0;
    begin = std::chrono::high_resolution_clock::now();

    std::vector<double> x = x0;
    std::vector<double> r(b.size()), d(b.size()), r1(b.size()); 
    double alpha = 0, betta = 0, storage = 0;
    r = csr * x - b;
    d = r;
    double rr = std::sqrt(r * r);

    while (rr > percision){
        alpha = (r * r) / (d * (csr * d));
        x = x - alpha * d;
        r1 = csr * x - b;
        storage = (r1 * r1);
        rr = std::sqrt(storage);
        if (rr <= percision) break;
        betta = storage / (r * r);
        d = r1 + betta * d;
        r = r1;
    }

    end = std::chrono::high_resolution_clock::now();
    counter << getValue() << std::endl;
    timer << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
    }
    timer.close();
    counter.close();
    std::cout << "ended" << std::endl;
    return 0;
}