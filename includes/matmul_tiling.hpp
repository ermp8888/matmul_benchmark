#include <iostream>
#include "matrix.hpp"
#include "matmul.hpp"

using namespace std;


namespace dlops{

template<typename T>
Matrix<T> tiledMatMul(const Matrix<T>& M1, const Matrix<T>& M2, int tileSize){
    assert(M1.numCols() == M2.numRows());
    int r1 = M1.numRows(), c1 = M1.numCols(), c2 = M2.numCols();

    Matrix<T> result(r1, c2);
    for(int tw = 0; tw < r1; tw += tileSize){
        for(int th = 0; th < c2; th += tileSize){
            for(int tk = 0; tk < c1; tk += tileSize){  // shared-dimension tiling
                matmul_ikj(M1, M2, result, tw, th, tk, tileSize);
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> tiledMatMulWithTranspose(const Matrix<T>& M1, const Matrix<T>& M2, int tileSize){
    assert(M1.numCols() == M2.numRows());
    int r1 = M1.numRows(), c1 = M1.numCols(), c2 = M2.numCols();

    Matrix<T> B_T = mat_transpose(M2);
    Matrix<T> result(r1, c2);
    for(int tw = 0; tw < r1; tw += tileSize){
        for(int th = 0; th < c2; th += tileSize){
            for(int tk = 0; tk < c1; tk += tileSize){  // shared-dimension tiling
                matmul_ijk(M1, B_T, result, tw, th, tk, tileSize);
            }
        }
    }
    return result;
}

} // namespace dlops