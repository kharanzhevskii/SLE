#include "../src/matrix/dense.h"
#include <chrono>
#include <fstream>

void dense_multiplier(){
    std::ofstream filefat;
    filefat.open ("dense_fat_O2.txt");
    std::ofstream filethin;
    filethin.open ("dense_thin_O2.txt");

    std::vector<int> values, mfat, mthin, result;
    std::chrono::high_resolution_clock::time_point begin, end;
    for (int n = 10; n <= 2500; n+=5){
        values.resize(n*n);
        mthin.resize(n);
        mfat.resize(n);

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if ((i-j) <= 1 && (i-j) >= -1){
                    values[n*i+j] = i+j;
                }
                else{
                    values[n*i+j] = 0;
                }
            }
        }

        for (int i = 0; i < n; i++){ // all non-zero elememts
            mfat[i] = n - i;
        }
        for (int i = 0; i < n; i++){ // 20% non-zero elements
            mthin[i] = ((n - i) % 5 == 0) ? n-i : 0;
        }

        Dense dense(values, n, n);

        begin = std::chrono::high_resolution_clock::now();
        result = dense * mfat;
        end = std::chrono::high_resolution_clock::now();
        filefat << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;

        begin = std::chrono::high_resolution_clock::now();
        result = dense * mthin;
        end = std::chrono::high_resolution_clock::now();
        filethin << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;

        values.clear();
        mfat.clear();
        mthin.clear();
    }
    filethin.close();
    filefat.close();
}

int main(){
    dense_multiplier();
    return 0;
}