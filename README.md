# System-of-linear-equations-solver

## Description
##### Simple console application that finds solutions of a collection of linear equations with the same set of variables expressed in the matrix form **Ax=b**, provided in txt file.
##### If the matrix A is square, then the soultions are given by x =A<sup>-1</sup>*b, where a<sup>-1</sup> is a inverse of matrix A

## Text File Format

If we want to find real solutions of our linear system we need to provide a name of text file **with** .txt extension as a command line argument
The file must include a dimension, coefficients and constant terms of the system.

Both the file and application have to be placed in the same folder.

Example form of a text file

```
5                   //dimension    
1 2 3 4 4   1       //coefficients and constant terms of the first equation  
1 5 3 4 6   4       //coefficients and constant terms of the second equation  
2 2 8 3 6   5       //coefficients and constant terms of the third equation  
4 5 2 1 8   6       //coefficients and constant terms of the fourth equation  
9 0 2 7 4   2       //coefficients and constant terms of the fifth equation  
```
The example file titled ***Macierz.txt*** has been included to repository.
