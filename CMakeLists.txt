cmake_minimum_required(VERSION 3.16)

project(Matrix C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Matrix.hpp
)

set(Sources
    Matrix.cpp
)

add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})

add_subdirectory(Test)