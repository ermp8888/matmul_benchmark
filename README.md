# dlops

A lightweight C++ library for matrix operations with a focus on performance benchmarking and experimentation.

## ✨ Features

- **Generic Matrix class** (templated for flexibility)
- **Multiple matrix multiplication algorithms**:  
  - Standard (ijk, ikj)  
  - Transposed  
  - Tiled (cache-optimized)
- **Matrix initialization utilities** (random / sequential filling)
- **Ready-to-use benchmarks and tests**

## 🚀 Build Instructions

This project uses **CMake (>= 3.15)**:

```sh
git clone https://github.com/ermp8888/matmul_benchmark.git
cd dlops
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## 📊 Run Benchmarks

```sh
./bench_matmul <rows_A> <cols_A> <rows_B> <cols_B> <tile_size>
```

Example:

```sh
./bench_matmul 512 512 512 512 32
```

## ✅ Run Tests

```sh
./test_matmul <rows_A> <cols_A> <rows_B> <cols_B>
```

Example:

```sh
./test_matmul 128 128 128 128
```

## 📂 Directory Structure

```
dlops/
├── benchmarks/        # Benchmark executables
├── include/           # Header files
├── src/               # Source files
├── tests/             # Test executables
├── .github/workflows/ # CI/CD pipeline
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## 🛠️ Roadmap

- [ ] Add more advanced tiling strategies  
- [ ] SIMD (AVX/NEON) optimizations  
- [ ] Add CI/CD pipeline with unit testing  
- [ ] Extend benchmarks with memory profiling  

## 📜 License

This project is licensed under the [MIT License](LICENSE).
