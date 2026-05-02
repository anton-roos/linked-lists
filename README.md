# COS2611 - Data Structures and Algorithms

This repository contains coursework for **COS2611**, a module offered by the University of South Africa (UNISA) that focuses on fundamental data structures and algorithms used in computer science.

## Module Overview

COS2611 introduces students to essential data structures and their applications in solving real-world computational problems. The module covers:

- **Linear Data Structures**: Arrays, Linked Lists, Stacks, and Queues
- **Algorithms**: Searching, Sorting, and Traversal techniques
- **Application Design**: Using appropriate data structures to solve complex problems
- **Complexity Analysis**: Understanding time and space complexity of algorithms

## Project Structure

```
cos2611/
├── src/                        # Source code relating to the module
├── Abstractions.cpp            # Supporting data structure implementations
└── README.md                   # This file
```

## Key Assignments

### Assignment 1: Warehouse Order Dispatch Simulation

A simulation program that models a warehouse order processing system using fundamental data structures:

**Concepts Demonstrated:**
- **Queues**: Three separate queues for different order types (Small, Medium, Big)
- **Stacks**: Stack of dispatched trucks to track order fulfillment
- **Maps**: Tracking truck and processing counters
- **Vectors**: Logging orders for reporting

**Features:**
- Random order generation with varying processing times
- Truck dispatch logic based on queue capacity and order priority
- Comprehensive reporting of generated orders and dispatched trucks
- Time-step simulation over 30 time units

**Running the Simulation:**
```bash
g++ src/62233467_AS1.cpp -o warehouse_sim
./warehouse_sim
```

## Learning Objectives

By studying this code, you will understand:

1. How to implement and manipulate fundamental data structures
2. How different data structures are suited for different problems
3. Queue and stack operations in practical applications
4. Simulation design and random event generation
5. C++ STL containers (queue, stack, vector, map)

## Building and Compiling

### Prerequisites
- g++ compiler (or equivalent C++ compiler)
- C++11 or later standard

### Compilation
```bash
# Compile individual assignment
g++ src/62233467_AS1.cpp -o assignment1

# Compile linked list examples
g++ src/CodeA.cpp -o linkedlist_example
```

## Code Style and Structure

The code follows standard C++ practices:
- Clear separation of concerns (data structures vs. simulation logic)
- Structured output with formatted reports
- Appropriate use of STL containers
- Comments explaining key logic and algorithms

## Additional Resources

- **UNISA Official**: [https://www.unisa.ac.za/](https://www.unisa.ac.za/)
- **COS2611 Study Guide**: Refer to your course materials
- **C++ Reference**: [cppreference.com](https://en.cppreference.com/)

---

**Student Number**: 62233467  
**Module Code**: COS2611  
**Institution**: University of South Africa (UNISA)