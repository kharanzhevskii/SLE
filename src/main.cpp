#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "tridiagonal.h"

int main(int argc, char** argv){
    if (argc <= 1) exit(1);
    std::string filename = argv[1];
    std::ifstream file;
	file.open(filename);

	int n;
	file >> n;
    n--;
	
	std::vector<double> A(4*n+2, 0);
	for (int i = 0; i < 4*n+2; i++) {
			file >> A[i];
	}
    
    std::vector<double> answer = tridiagonal(A, n);
    for (int i = 0; i < n+1; i++){
        std::cout << answer[i] << std::endl;
    }
    return 0;
}