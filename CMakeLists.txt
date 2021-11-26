cmake_minimum_required(VERSION 3.10)
project(armasimu VERSION 1.0)


add_executable(armasimu "src/main.cc" "src/system.cc")
include_directories("dep" "include")
target_link_libraries(armasimu dep/linker/armadillo dep/linker/blas_win64_MT dep/linker/lapack_win64_MT)
