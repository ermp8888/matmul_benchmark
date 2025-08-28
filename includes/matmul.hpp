#include "matrix.hpp"

namespace dlops {

// Method 1 (i-j-k)
template<typename T>
Matrix<T> matmul_ijk(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.numCols() == B.numRows());
    int r1 = A.numRows(), c1 = A.numCols(), c2 = B.numCols();

    Matrix<T> C(r1, c2, 0);

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            T sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }
    return C;
}

// Method 2 (i-k-j)
template<typename T>
Matrix<T> matmul_ikj(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.numCols() == B.numRows());
    int r1 = A.numRows(), c1 = A.numCols(), c2 = B.numCols();

    Matrix<T> C(r1, c2, 0);

    for (int i = 0; i < r1; i++) {
        for (int k = 0; k < c1; k++) {
            for (int j = 0; j < c2; j++) {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}

template<typename T>
Matrix<T> mat_transpose(const Matrix<T> &A){
    int rows = A.numRows();
    int cols = A.numCols();
    Matrix<T> B(cols, rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            B(j, i) = A(i, j);
        }
    }
    return B;
}

template<typename T>
Matrix<T> matmul_transpose(const Matrix<T>& A, const Matrix<T>& B){
    assert(A.numCols() == B.numRows());
    int r1 = A.numRows(), c1 = A.numCols(), c2 = B.numCols();

    Matrix<T> C(r1, c2, 0);
    Matrix<T> B_T = mat_transpose(B);
    for(int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            T sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += A(i, k) * B_T(j, k);
            }
            C(i, j) = sum;
        }
    }
    return C;
}
template<typename T>
Matrix<T> matmul_ref(const Matrix<T>& M1, const Matrix<T>& M2) {
    assert(M1.numCols() == M2.numRows());
    int r1 = M1.numRows(), c1 = M1.numCols(), c2 = M2.numCols();

    Matrix<T> result(r1, c2, 0);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result(i, j) += M1(i, k) * M2(k, j);
            }
        }
    }
    return result;
}


// Explicit instantiations
template Matrix<int> matmul_ref(const Matrix<int>&, const Matrix<int>&);
template Matrix<float> matmul_ref(const Matrix<float>&, const Matrix<float>&);
template Matrix<int> mat_transpose(const Matrix<int>&);
template Matrix<float> mat_transpose(const Matrix<float>&);
template Matrix<int> matmul_ijk(const Matrix<int>&, const Matrix<int>&);
template Matrix<int> matmul_ikj(const Matrix<int>&, const Matrix<int>&);
template Matrix<float> matmul_ijk(const Matrix<float>&, const Matrix<float>&);
template Matrix<float> matmul_ikj(const Matrix<float>&, const Matrix<float>&);

} // namespace dlops
