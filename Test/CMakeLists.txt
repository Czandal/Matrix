cmake_minimum_required(VERSION 3.21)

set(This MatrixTests)

set(Sources 
MatrixTest.cpp)

add_executable(${This} ${Sources})
target_link_libraries( ${This} PUBLIC
     gtest_main
     Matrix
)

add_test(
    NAME ${This}
    COMMAND ${This}
)