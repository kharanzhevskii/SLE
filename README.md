# SLE

SLE is a C++ template library for solving Systems of Linear Equations with square matrices.

(/fun/Gradient_methods_on_contour/steps_contour.png)

The library is optimized for the fastest solution search, so errors and discrepancies of the method are **NOT** registered.

## Installation

- `src` - contains the source code. It is built as a `INTERFACE` library
- `tests` - contains unit tests. The `gtest` framework is used
- `fun` - code measuring convergence rates of different methods with visual representation (created via `matplotlib`)

### To install on Linux (Ubuntu)
1) Change the current working directory to the location where you want the cloned directory
2) Clone the repository using either URL or SSH key
```
git clone git@github.com:kharanzhevskii/SLE.git
```
3) Create subdirectory build in project directory to store make and cmake files
```
mkdir build && cd build
```
4) To compile with test use flag `-DWITH_TESTS=ON`
```
cmake .. -DWITH_TESTS=ON
make
```
5) Built files will be stored in `/src/CMakeFiles/SLE.dir`, while all test executables will be in `/test`. To use the library, add the subdirectory in your main CMakeLists.txt
```
add_subdirectory(relative_path)
```

## Usage
To use solvers, include their header files via relative path. In this example, subdirectory SLE is added to the main CMakeLists.txt, so the relative paths looks like this. All solver functions return the solution as vector `res`, however, arguments of different functions may vary as some methods require eigenvalues or external constants, so please, check the function declaration before using it. Good examples can be found in `/fun` folder.

```c++
#include "src/krylov/CG.h"
#include "src/matrix/elliptic.h"

int main() {
    const unsigned long int L = 256;
    const unsigned long int N = L * L;
    CSR<double> csr = elliptic(L, 1.0, 5.0);    // create elliptic matrix with given constants
    std::vector<double> b(N, 0), res(N, 0), x0(N, 1);    // columns for b, result and initial approximation x0
    const double percision = 1e-8;    // determine percision
    res = CG(csr, b, x0, percision);    // solve the equation
    std::cout << res;    // print out the result
    return 0;
}
```

## Contributing

For major changes, please open an issue to discuss what you would like to change.

Pull requests are welcome. Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)