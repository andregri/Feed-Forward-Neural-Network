# Feed-Forward-Neural-Network

C++ implementation of a Feed Forward Neural Network.

## Building

```
cmake .
make
```

## Video contents and review

https://www.youtube.com/watch?v=c69KRgtmNSY&list=PL2-7U6BzddIYBOl98DDsmpXiTcj1ojgJG&index=2

0. *Good*: project setup with CMake. Implementation of the **Neuron class**.

1. *Nice*: implementation of the **Layer, Matrix and NeuralNetwork classes**.
I fixed all the memory leaks with `valgrind --leak-check=full ./opeann`.
I understood the importance of a good IDE.

2. *Very bad*: code review of the **feedForward** function. The code is already
implemented and it is not clean. I added the operator overloading for
the matrices product.

3. *Normal*: code review of the error functions.

4. *Bad*: implementation of the back propagation is very messy.

5. *Normal*: quadratic cost function instead of absolute error.

## Resources

- https://vimeo.com/19569529 (to see)