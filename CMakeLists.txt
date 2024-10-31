cmake_minimum_required(VERSION 3.5.0)
project(image VERSION 0.1.0 LANGUAGES C CXX)

add_executable(image ppmviewer.cpp)

include(CTest)
enable_testing()

