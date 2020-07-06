# Feed-Forward-Neural-Network

C++ implementation of a Feed Forward Neural Network.

## Building

```
cmake .
make
```

## Video contents and review

https://www.youtube.com/watch?v=c69KRgtmNSY&list=PL2-7U6BzddIYBOl98DDsmpXiTcj1ojgJG&index=2

1. *Good*: project setup with CMake. Implementation of the **Neuron class**.

2. *Nice*: implementation of the **Layer, Matrix and NeuralNetwork classes**.
I fixed all the memory leaks with `valgrind --leak-check=full ./opeann`.
I understood the importance of a good IDE.

3. *Very bad*: code review of the **feedForward** function. The code is already
implemented and it is not clean. I added the operator overloading for
the matrices product.