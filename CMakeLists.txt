cmake_minimum_required(VERSION 3.27)
project(Advanced_Tree_Data_Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(Advanced_Tree_Data_Structures main.cpp
        Header/TwoThreeHeap.h
        Source/TwoThreeHeap.cpp
        Header/FibonacciHeap.h
        Source/FibonacciHeap.cpp
        Header/BinaryHeap.h
        Source/BinaryHeap.cpp)
