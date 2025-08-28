#include "../includes/matmul.hpp"
#include <iostream>

using namespace dlops;

int main() {
    Matrix<int> A(2, 3, 1);  // 2x3 filled with 1s
    Matrix<int> B(3, 2, 2);  // 3x2 filled with 2s
    Matrix<int> C(5, 5);

    C.fillSeq();

    auto C1 = matmul_ijk(A, B);
    auto C2 = matmul_ikj(A, B);

    std::cout << "Result (ijk):\n";
    C1.print();

    std::cout << "\nResult (ikj):\n";
    C2.print();

    std::cout << "\nMatrix C (5x5 filled sequentially):\n";
    C.print();
}
