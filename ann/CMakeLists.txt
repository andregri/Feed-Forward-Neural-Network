cmake_minimum_required(VERSION 3.7)
project(ann)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(
    ann
    src/main.cpp
    src/Neuron.cpp
)