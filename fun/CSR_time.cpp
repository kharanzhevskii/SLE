#include "../src/matrix/CSR.h"
#include <chrono>
#include <fstream>

void CSR_multiplier(){
    std::ofstream filefat;
    filefat.open ("CSR_fat_O0.txt");
    std::ofstream filethin;
    filethin.open ("CSR_thin_O0.txt");

    std::vector<int> values, cols, rows, mfat, mthin, result;
    int num;
    std::chrono::high_resolution_clock::time_point begin, end;
    for (int n = 10; n <= 2500; n+=5){
        values.resize(3*n-2);
        cols.resize(3*n-2);
        rows.resize(n+1);
        mthin.resize(n);
        mfat.resize(n);

        values[0] = 1;
        values[1] = 1;
        num = 1;
        for (int i = 2; i <= 3*n-7; i+=3){
            values[i] = num;
            values[i+1] = num+1;
            values[i+2] = num+2;
            num+=2;
        }
        values[3*n-4] = 2*n-3;
        values[3*n-3] = 2*n-2;

        cols[0] = 1;
        cols[1] = 1;
        num = 0;
        for (int i = 2; i <= 3*n-7; i+=3){
            cols[i] = num;
            cols[i+1] = num+1;
            cols[i+2] = num+2;
            num++;
        }
        cols[3*n-4] = n-2;
        cols[3*n-3] = n-1;

        rows[0] = 0;
        rows[1] = 2;
        num = 5;
        for (int i = 2; i <= n-1; i++){
            rows[i] = num;
            num+=3;
        }
        rows[n] = 3*n-2;

        for (int i = 0; i < n; i++){ // all non-zero elememts
            mfat[i] = n - i;
        }
        for (int i = 0; i < n; i++){ // 20% non-zero elements
            mthin[i] = ((n - i) % 5 == 0) ? n-i : 0;
        }

        CSR csr(values, cols, rows);

        begin = std::chrono::high_resolution_clock::now();
        result = csr * mfat;
        end = std::chrono::high_resolution_clock::now();
        filefat << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;

        begin = std::chrono::high_resolution_clock::now();
        result = csr * mthin;
        end = std::chrono::high_resolution_clock::now();
        filethin << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;

        values.clear();
        cols.clear();
        rows.clear();
        mfat.clear();
        mthin.clear();
        num = 0;
    }
    filethin.close();
    filefat.close();
}

int main(){
    CSR_multiplier();
    return 0;
}