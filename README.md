# Budget Allocation using Subset Sum Algorithms

---

## \#\# Command-Line Interface (CLI) User Guide

This guide explains how to use the `SubsetSumSolver` command-line tool.

### **1. Overview**

`SubsetSumSolver` is a high-performance C++ tool for solving the Subset Sum Problem. It features multiple algorithms, benchmarking capabilities, and the ability to save results to a PostgreSQL database.

### **2. Compilation**

Before running, you must compile the project from the root directory:

```bash
# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Compile the code
cmake --build .
```

This will create the `solver` executable inside the `build` directory.

### **3. Usage**

The solver is run from within the `build` directory (`./solver`).

**Basic Syntax:**
`./solver [INPUT_OPTIONS] [ALGORITHM_OPTIONS] [ACTION_OPTIONS]`

#### **Input Options (Choose one method)**

  * **Direct Input**: Provide numbers and a target directly.

    ```bash
    ./solver -n 3,34,4,12,5,2 -t 9
    ```

      * `-n, --numbers`: A comma-separated string of integers (no spaces).
      * `-t, --target`: The integer target sum.

  * **File Input**: Provide a path to a text file.

    ```bash
    ./solver -f ../input.txt
    ```

      * The file must contain two lines:
        1.  A comma-separated list of numbers.
        2.  The target sum.

#### **Algorithm and Mode Options**

  * `--algo <type>`: Selects the algorithm.

      * `dp`: **Dynamic Programming** (default). Fast and memory-intensive.
      * `backtrack`: **Backtracking**. Slower for some problems but uses less memory and supports finding all subsets.

    <!-- end list -->

    ```bash
    ./solver -n 1,2,3,4,5 -t 6 --algo backtrack
    ```

  * `--find-all`: Finds all possible subsets that sum to the target.

      * **Note**: This option only works with the `backtrack` algorithm.

    <!-- end list -->

    ```bash
    ./solver -n 1,2,3,4,5,6 -t 6 --algo backtrack --find-all
    ```

#### **Action Options**

  * `-s, --save`: Saves the solver's result to the PostgreSQL database.

      * **Niche Requirement**: This action executes the `db_handler.py` script. You must have **Python 3** and the `psycopg2-binary` library installed (`pip install psycopg2-binary`).
      * The database connection settings (`dbname`, `user`, `password`) are hardcoded in the Python script.

    <!-- end list -->

    ```bash
    ./solver -n 1,5,2,8 -t 10 --save
    ```

  * `-b <N>, --benchmark <N>`: Runs the solver `N` times and prints performance statistics.

      * The `--save` flag is ignored in benchmark mode.

    <!-- end list -->

    ```bash
    # Benchmark the DP algorithm 1000 times
    ./solver -n 3,34,4,12,5,2,8,1,7 -t 22 -b 1000
    ```

-----

## \#\# Contributor `README.md`

This `README.md` is for developers who want to contribute to or understand the project's architecture.

````markdown
# C++ Subset Sum Solver

A high-performance, modular C++ application for solving the Subset Sum Problem, featuring multiple algorithms, a full-featured CLI, benchmarking, and database integration via a Python microservice.

## Project Overview

This project is architected with a clean separation of concerns, prioritizing a robust, testable C++ core with a decoupled database handler to ensure stability and avoid complex library dependency issues.

- **Core Engine (C++)**: High-performance solver logic.
- **User Interface (C++)**: A command-line interface for user interaction.
- **Database Handler (Python)**: A simple microservice that handles all PostgreSQL communication, called by the C++ core.

## Getting Started

### Prerequisites

- A modern C++ compiler (GCC 11+, Clang 12+)
- CMake (version 3.14+)
- Python 3
- `pip` for Python package management
- PostgreSQL server

### Build Instructions

1.  **Clone the Repository**:
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Install Python Dependencies**:
    ```bash
    pip install psycopg2-binary
    ```

3.  **Setup the Database**:
    - Ensure your PostgreSQL server is running.
    - Create a user and database. The Python script defaults to `dbname=subset_solver_db`, `user=user1`, `password=password1`.
    - Apply the schema by executing the SQL commands in `schema.sql` (Note: You should create this file from the schema provided earlier).

4.  **Compile the C++ Application**:
    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ```
    The executables (`solver` and `run_tests`) will be in the `build` directory.

---

## Code Architecture

The project is structured into distinct, modular components located in the `src/` directory.

- **`CoreSolver/`**: Contains the implementations for the subset sum algorithms (`DpSolver.cpp`, `BacktrackingSolver.cpp`), all inheriting from the `ISubsetSumSolver` interface.

- **`AlgorithmSelector/`**: Implements the Factory pattern (`SolverFactory.cpp`) to create solver objects based on user input (e.g., "dp" or "backtrack").

- **`DataModel/`**: Defines the plain C++ structs used throughout the application, such as `DataSet.h` and `SolverResult.h`.

- **`Benchmarking/`**: Includes a `BenchmarkRunner` class to perform repeated runs of any solver for performance analysis.

- **`include/`**: Contains external single-header libraries, such as `nlohmann/json.hpp`.

- **`main.cpp`**: The entry point for the CLI application. It uses the `cxxopts` library to parse arguments and orchestrates calls to the other modules.

### A Niche Architectural Note: The Python Bridge

A key design decision was to separate the database logic into a Python script (`db_handler.py`).

-   **Why?** Early development with a C++ PostgreSQL library (`libpqxx`) revealed a severe **ABI (Application Binary Interface) mismatch**. The system's pre-compiled library was built against an older C++ standard than our project, causing memory corruption (`double free`) on exit.
-   **Solution**: Instead of forcing a custom build of `libpqxx`, we adopted a microservice architecture. The C++ core serializes its result to JSON and pipes it to the Python script. This completely decouples the C++ build from the database driver, eliminating all ABI issues and making the system more robust.

---

## How to Contribute

### Running Tests

This project uses the Google Test framework. The tests are located in the `tests/` directory and are automatically compiled into the `run_tests` executable.

To run the tests, execute from the `build` directory:
```bash
./run_tests
````

### Memory Debugging (A Niche Tool)

Memory errors can be diagnosed using `valgrind`. It should be run from the `build` directory. A clean run will report "0 errors from 0 contexts."

```bash
valgrind ./solver -n 1,2,3,4,5 -t 6 --save
```

### Code Style

  - Follow the existing modern C++17 conventions.
  - Use `std::unique_ptr` for managing ownership of heap-allocated objects.
  - Ensure new CLI options are documented in the user guide.
  - Write unit tests for any new algorithms or complex logic.

<!-- end list -->

```
```
