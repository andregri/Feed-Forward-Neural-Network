cmake_minimum_required(VERSION 3.7)
project(ann)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread -std=c++14")

add_executable(
    ann
    src/main.cpp
    src/Neuron.cpp
    src/Matrix.cpp
    src/Layer.cpp
    src/utils/Math.cpp
    src/neural_network/NeuralNetwork.cpp
    src/neural_network/feedForward.cpp
    src/neural_network/setErrors.cpp
    src/neural_network/backPropagation.cpp
    src/neural_network/train.cpp
)