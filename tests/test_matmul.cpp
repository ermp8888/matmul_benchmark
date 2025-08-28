#include "../includes/matrix.hpp"
#include "../includes/matmul.hpp"
#include "../includes/matmul_tiling.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>  // for std::atoi
#include <cmath>   // for std::fabs

using namespace dlops;

template<typename T>
bool compareMatrices(const Matrix<T>& A, const Matrix<T>& B, double tol = 1e-6) {
    if (A.numRows() != B.numRows() || A.numCols() != B.numCols()) {
        std::cerr << "Dimension mismatch: (" << A.numRows() << "x" << A.numCols()
                  << ") vs (" << B.numRows() << "x" << B.numCols() << ")\n";
        return false;
    }

    for (int i = 0; i < A.numRows(); i++) {
        for (int j = 0; j < A.numCols(); j++) {
            T valA = A(i, j);
            T valB = B(i, j);

            if constexpr (std::is_floating_point<T>::value) {
                if (std::fabs(valA - valB) > tol) {
                    std::cerr << "Mismatch at (" << i << "," << j 
                              << "): " << valA << " vs " << valB << "\n";
                    return false;
                }
            } else { // For int/long long etc.
                if (valA != valB) {
                    std::cerr << "Mismatch at (" << i << "," << j 
                              << "): " << valA << " vs " << valB << "\n";
                    return false;
                }
            }
        }
    }
    return true;
}



int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] 
                  << " <rows_A> <cols_A> <rows_B> <cols_B>\n";
        return 1;
    }
    int rows_A = std::atoi(argv[1]);
    int cols_A = std::atoi(argv[2]);
    int rows_B = std::atoi(argv[3]);
    int cols_B = std::atoi(argv[4]);

    assert(cols_A == rows_B && "Matrix dimensions do not match for multiplication");

    Matrix<int> A(rows_A, cols_A), B(rows_B, cols_B);

    A.fillSeq();
    B.fillSeq();

    auto C_ref = matmul_ref(A, B);
    auto C_ijk = matmul_ijk(A, B);
    auto C_ikj = matmul_ikj(A, B);
    auto C_transpose = mat_transpose(A);
    auto C_transpose_mult = matmul_transpose(A, B);
    auto C_tiled = tiledMatMul(A, B, 16); // tile size 16

    bool pass = true;
    pass &= compareMatrices(C_ref, C_ijk);
    pass &= compareMatrices(C_ref, C_ikj);
    pass &= compareMatrices(C_ref, C_transpose_mult);
    pass &= compareMatrices(C_ref, C_tiled);

    if (pass) {
        std::cout << "All matmul tests passed!\n";
    } else {
        std::cerr << "Some tests failed!\n";
    }


    // std::cout << "Checking matmul_ijk: " << (compareMatrices(C_ref, C_ijk) ? "PASS" : "FAIL") << "\n";
    // std::cout << "Checking matmul_ikj: " << (compareMatrices(C_ref, C_ikj) ? "PASS" : "FAIL") << "\n";
    // // std::cout << "Checking matmul_transpose: " << (compareMatrices(C_ref, C_transpose) ? "PASS" : "FAIL") << "\n";
    // std::cout << "Checking matmul_transpose_mult: " << (compareMatrices(C_ref, C_transpose_mult) ? "PASS" : "FAIL") << "\n";

    return 0;
}
