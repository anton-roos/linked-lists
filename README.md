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

A simulation program that models a warehouse order processing system using fundamental data structures.

**File**: `src/62233467_AS1.cpp`

#### Rubric Compliance

| Criterion | Implementation | Location |
|-----------|-----------------|----------|
| **Student Info** | Name and student number in first 3 lines | Lines 1-3 |
| **File Format** | Correct naming: `62233467_AS1.cpp` | Filename |
| **Standard Libraries** | Uses only STL headers (iostream, queue, stack, vector, random, string, map, array) | Lines 5-12 |
| **Queue Processing** (6 marks) | Three queues (S, M, B) with front element decrements and removal when complete | Lines 65-67, 113-140 |
| **Stack Dispatch** (5 marks) | Truck labels pushed to stack when capacity reached; proper LIFO ordering | Lines 70, 129-137 |
| **Time-step Simulation** (5 marks) | 30 time-step loop with accurate decrement of processing times | Lines 91-166 |
| **Random Generation** (3 marks) | Mersenne Twister generator with distributions for arrivals, types, and processing times | Lines 79-84, 93-110 |
| **Output Formatting** (3 marks) | Clear structured output with time steps, queues, stack state, and new arrivals | Lines 142-165 |
| **Code Quality** (4 marks) | Well-structured code with helper functions, clear comments, and modular design | Throughout |
| **Order Report** (4 marks) | CSV-formatted table of all generated orders at program end | Lines 169-172 |
| **Bonus Features** | Structured OrderLogEntry data, helper functions (printQueue, printStack), modular design | Lines 18-23, 29-55 |

**Concepts Demonstrated:**
- **Queues**: Three separate queues for different order types (Small, Medium, Big) with proper FIFO operations
- **Stacks**: Stack of dispatched trucks to track order fulfillment history
- **Maps**: Tracking truck and processing counters by order type
- **Vectors**: Logging orders and new arrivals for comprehensive reporting
- **Random Number Generation**: Realistic simulation of order arrivals with varying types and processing times

**Features:**
- Random order generation with varying processing times (1-4 units)
- Variable order arrivals per time step (0-3 orders)
- Truck dispatch logic: creates and dispatches truck when 5 orders of same type complete
- Real-time simulation output showing queue state and truck dispatch history
- Final CSV report of all generated orders for analysis

**Running the Simulation:**
```bash
g++ src/62233467_AS1.cpp -o warehouse_sim
./warehouse_sim
```

**Sample Output Format:**
```
=== Warehouse Order Dispatch Simulation ===
Time steps: 30, Truck capacity: 5

Time Step: 1
New Orders: S, M
Queue S: [S(3)]
Queue M: [M(2)]
Queue B: []
Stack: empty

... (28 more time steps) ...

time_step,type,processing_time
1,S,3
1,M,2
... (all generated orders in CSV format)
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