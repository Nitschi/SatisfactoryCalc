cmake_minimum_required(VERSION 3.15)

set(This SatisfactoryCalc)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SatisfactoryCalc)
add_subdirectory(SatisfactoryCalcMain)
