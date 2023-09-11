cmake_minimum_required(VERSION 3.23)
project(seqDerivCheck)

set(CMAKE_CXX_STANDARD 17)

add_executable(seqDerivCheck main.cpp Quine_meth.cpp Reduct_meth.cpp pre_process.cpp)
