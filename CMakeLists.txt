# cmake_minimum_required(VERSION 3.15)
# project(dlops LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # include directory
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # source files
# add_library(dlops STATIC src/main.cpp)

# # benchmark executable
# add_executable(bench_matmul benchmarks/bench_matmul.cpp)
# target_link_libraries(bench_matmul dlops)

# # test executable
# add_executable(test_matmul tests/test_matmul.cpp)
# target_link_libraries(test_matmul dlops)

# # main executable
# add_executable(main_exec src/main.cpp)
# target_link_libraries(main_exec dlops)



cmake_minimum_required(VERSION 3.15)
project(dlops LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Release build and optimization flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -funroll-loops -ffast-math")

# include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# source files
add_library(dlops STATIC src/main.cpp)

# benchmark executable
add_executable(bench_matmul benchmarks/bench_matmul.cpp)
target_link_libraries(bench_matmul dlops)

# test executable
add_executable(test_matmul tests/test_matmul.cpp)
target_link_libraries(test_matmul dlops)

# main executable
add_executable(main_exec src/main.cpp)
target_link_libraries(main_exec dlops)
