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

#### Genetic algorithm

After parsing the problem into a program structure, a genetic algorithm will be used to determine or approximate the optimal solution. For this a population of a given size containing agents will be created. Each of those agents will be initialized with the minimum values of each variable. In each generation, the fitness of these agents will be determine based on the following formula:
```
```
After that, the best agent will be put in the next generation. The rest of the other population is based on the remaining agent; the higher the fitness of an agent, the higher the probability, that the agent will be put in the next generation. When an agent is put in the next generation, with a given mutation probability, its values will mutate in a given mutation range. The process is repeated for a given number of epoches.

#### What's to come
In the near future, the implementation of the genetic algorithm will be improved and new types of optimization problems will be implemented. Stay tuned!