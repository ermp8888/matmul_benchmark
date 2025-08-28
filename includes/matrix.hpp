#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

namespace dlops {

template<typename T>
class Matrix {
private:
    int rows, cols;
    std::vector<T> data;

public:
    Matrix(int r, int c, T initVal = 0) 
        : rows(r), cols(c), data(r*c, initVal) {}

    T& operator()(int i, int j) {
        return data[i * cols + j];
    }
    const T& operator()(int i, int j) const {
        return data[i * cols + j];
    }

    int numRows() const { return rows; }
    int numCols() const { return cols; }
    const std::vector<T>& raw() const { return data; }
    std::vector<T>& raw() { return data; }

    void fillRandom(T minVal = 0, T maxVal = 10) {
        for (auto &x : data) {
            x = static_cast<T>(minVal + rand() % (maxVal - minVal + 1));
        }
    }
    void fillSeq(){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)(i, j) = static_cast<T>(i * cols + j);
            }
        }
    }

    void print(int maxRows = 5, int maxCols = 5) const {
        int r = std::min(rows, maxRows);
        int c = std::min(cols, maxCols);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                std::cout << std::setw(6) << operator()(i, j) << " ";
            }
            if (c < cols) std::cout << "...";
            std::cout << "\n";
        }
        if (r < rows) std::cout << "...\n";
    }
};

} // namespace dlops
