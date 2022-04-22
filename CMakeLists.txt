cmake_minimum_required(VERSION 3.19)
project(fk)

set(CMAKE_CXX_STANDARD 11)

add_executable(fk main.cpp src/fk/inverse.h)

enable_testing()
add_executable(fktest tester.cpp)
add_test(Tester fktest)