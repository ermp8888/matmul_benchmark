#include <iostream>
#include "matrix.hpp"

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
                for(int i = tw; i < min(tw + tileSize, r1); i++){
                    for(int k = th; k < min(th + tileSize, c1); k++){
                        for(int j = tk; j < min(tk + tileSize, c2); j++){
                            result(i, j) += M1(i, k) * M2(k, j);
                        }
                    }
                }
            }
        }
    }
    return result;
}

} // namespace dlops