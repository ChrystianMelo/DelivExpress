# DelivExpress - Optimizing Pathfinding Strategies

## Introduction

This project addresses a logistical challenge faced by **DelivExpress**, a startup in e-commerce, in determining the most efficient distribution routes. Given a set of cities connected by roads with specific distances, the goal is to **find the shortest path that visits all cities exactly once and returns to the starting point**.

To solve this, three different algorithmic approaches are implemented and compared:

1. **Brute Force:** Exhaustively evaluates all possible routes to find the optimal solution.
2. **Dynamic Programming:** Optimizes computations by storing intermediate results to improve performance.
3. **Greedy Algorithm:** Provides an approximate solution by making locally optimal choices at each step.

## Strategies

### 1. Brute Force
This approach evaluates all possible paths to determine the shortest one. While it guarantees the optimal solution, it becomes infeasible as the number of cities grows. The goal is to determine at what problem size brute force becomes impractical compared to the other methods.

### 2. Dynamic Programming
This approach improves efficiency by **storing previously computed solutions** to avoid redundant calculations. The objective is to measure **speed improvement** and **memory usage trade-offs** compared to brute force.

### 3. Greedy Algorithm
Unlike the previous strategies, the greedy approach does not guarantee an optimal solution but aims for a **good enough** one. It incrementally builds the solution by **choosing the locally best option at each step**. The analysis involves comparing **time and space complexity** with the other methods and evaluating **the quality of the obtained solution** relative to the optimal one.

## Implementation

### Programming Language
The project is implemented in **C/C++** using only standard libraries.

### Compilation
To compile the project, use:
```sh
make
```
The executable file will be named `tp3`.

### Input & Output
- **Input:**  
  - The first line contains a character indicating the strategy to use:  
    - `b` for Brute Force  
    - `d` for Dynamic Programming  
    - `g` for Greedy Algorithm  
  - The second line contains two integers `V E`, where `V` is the number of cities and `E` is the number of roads.
  - The next `E` lines each contain two city names and an integer `W`, representing the road distance between them.

- **Output:**  
  - The first line prints the total cost of the best route found.
  - The second line prints the sequence of cities forming the selected path.

### Example

#### **Input**
```
b
4 6
Brierbornedon Budwleyland 10
Brierbornedon Hallow 15
Brierbornedon Melodis 20
Budwleyland Hallow 35
Budwleyland Melodis 25
Hallow Melodis 30
```

#### **Output**
```
80
Brierbornedon Budwleyland Melodis Hallow
```

## Evaluation

The project is graded based on:
- **Correctness of results**
- **Execution time**
- **Code quality and readability**
- **Memory efficiency**

Ensure that your code **compiles without errors** and handles **edge cases** properly.

## Documentation

A report must be provided, including:
1. **Introduction** – Explanation of the problem.
2. **Modeling** – How the problem is structured in terms of data and algorithms.
3. **Solution** – Explanation of each approach and their comparative differences.
4. **Complexity Analysis** – Theoretical and empirical performance comparison.
5. **Final Considerations** – Challenges faced and lessons learned.
6. **References** – Sources consulted.

## Notes

- Follow **good coding practices** (consistent indentation, meaningful variable names, and modularization).
- Ensure compatibility with the **DCC computing environment**.
- Compilation must be **strict** (`-Wall -Wextra -Wpedantic -Werror`).
- Submissions **must include a Makefile** to generate the executable.

## License

This project is developed for educational purposes as part of **Algorithms I** coursework.
