#include "../includes/matrix.hpp"
#include "../includes/matmul.hpp"
#include "../includes/matmul_tiling.hpp"
#include <chrono>
#include <iostream>

using namespace dlops;

class Timer {
    using clock = std::chrono::high_resolution_clock;
    clock::time_point start;
public:
    Timer() { reset(); }
    void reset() { start = clock::now(); }

    // Elapsed time in seconds (double with fractions)
    double elapsedSec() const {
        return std::chrono::duration<double>(clock::now() - start).count();
    }

    // Elapsed time in milliseconds (double with fractions)
    double elapsedMilli() const {
        return std::chrono::duration<double, std::milli>(clock::now() - start).count();
    }
};

// Function to calculate performance change (%)
double performanceChange(double t1, double t2) {
    if (t1 == 0) {
        cerr << "Error: baseline time t1 cannot be zero." << endl;
        return 0.0;
    }
    return ((t1 - t2) / t1) * 100.0;
}

int main(int argc, char** argv) {

    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] 
                  << " <rows_A> <cols_A> <rows_B> <cols_B> <tile_size>\n";
        return 1;
    }

    int rows_A = std::atoi(argv[1]);
    int cols_A = std::atoi(argv[2]);
    int rows_B = std::atoi(argv[3]);
    int cols_B = std::atoi(argv[4]);
    int tile_size = std::atoi(argv[5]);

    assert(cols_A == rows_B && "Matrix dimensions do not match for multiplication");

    Matrix<int> A(rows_A, cols_A), B(rows_B, cols_B);
    A.fillRandom();
    B.fillRandom();

    // Benchmark method 1
    Timer t1;
    auto C1 = matmul_ijk(A, B);
    double timesec1 = t1.elapsedSec();
    double timemilsec1 = t1.elapsedMilli();
    double gflops1 = 2.0 * rows_A * cols_A * cols_B / (timesec1 * 1e9);

    // Benchmark method 2
    Timer t2;
    auto C2 = matmul_ikj(A, B);
    double timesec2 = t2.elapsedSec();
    double timemilsec2 = t2.elapsedMilli();
    double gflops2 = 2.0 * rows_A * cols_A * cols_B / (timesec2 * 1e9);

    // Benchmark method 3
    Timer t3;
    auto C3 = matmul_transpose(A, B);
    double timesec3 = t3.elapsedSec();
    double timemilsec3 = t3.elapsedMilli();
    double gflops3 = 2.0 * rows_A * cols_A * cols_B / (timesec3 * 1e9);

    // Benchmark method 4 (tiled)
    Timer t4;
    auto c4 = tiledMatMul(A, B, tile_size); // tile size from argument
    double timesec4 = t4.elapsedSec();
    double timemilsec4 = t4.elapsedMilli();
    double gflops4 = 2.0 * rows_A * cols_A * cols_B / (timesec4 * 1e9);

    // Benchmark method 4 (transpose with tiled)
    Timer t5;
    auto c5 = tiledMatMulWithTranspose(A, B, tile_size);
    double timesec5 = t5.elapsedSec();
    double timemilsec5 = t5.elapsedMilli();
    double gflops5 = 2.0 * rows_A * cols_A * cols_B / (timesec5 * 1e9);

    
    std::cout << "Matrix size: " << rows_A << "x" << cols_B << "\n";
    std::cout << "Method (i-j-k): " << timemilsec1 << " ms, " << gflops1 << " GFLOPS\n" << endl;
    std::cout << "Method (i-k-j): " << timemilsec2 << " ms, " << gflops2 << " GFLOPS\n" << " Perf Change: " << performanceChange(timemilsec1, timemilsec2) << "%\n";
    std::cout << "Method (transposed): " << timemilsec3 << " ms, " << gflops3 << " GFLOPS\n" << " Perf Change: " << performanceChange(timemilsec1, timemilsec3) << "%\n";
    std::cout << "Method (tiled): " << timemilsec4 << " ms, " << gflops4 << " GFLOPS\n" << " Perf Change: " << performanceChange(timemilsec1, timemilsec4) << "%\n";
    std::cout << "Method (tiled with transpose): " << timemilsec5 << " ms, " << gflops5 << " GFLOPS\n" << " Perf Change: " << performanceChange(timemilsec1, timemilsec5) << "%\n";

    return 0;
}
