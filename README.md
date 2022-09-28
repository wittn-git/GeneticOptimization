## GeneticOptimization
This project is a from-scratch build of an genetic algorithm to achieve mathematical optimization.

### Description
In this project, I want to build tools to input an optimization problem as a text file and use a genetic algorithm to solve for or at least approximate the optimal solution for the given problem. The program should read an input file and parse the contents into a dedicated data structure. Then a population of values for each variable of the program should be created. After those values are evaluated, the next generation of the population will be determined by the results of the previous one, allowing slight mutations. Hopefully, as the generations progress, after some time, an optimal solution or at least an approximation to it should be reached.

### Input format

The input format for the optimization problem is pretty straight forward. It contains definitions of used variabes, a maximizing objective and a number of equations functioning as constraints:
```
definitions:
x:[0,10];
y:[0,6];
objective:
4x + y
constraints:
2x >= 4;
y + x <= 10;
    .
    .
    .
```
In the following definitions, T is a Term, I is any identifier defined using alphabetic characters and N is an integer.

Following types of definitions are currently supported: 
- I:[N,N]

Following types of equations are currently supported:
- T == T
- T <= T
- T >= T

Following types of terms are currently supported:
- T + T
- T - T
- I
- N
- IN

#### What's to come
In the near future, the implementation of the genetic algorithm will follow. Stay tuned!