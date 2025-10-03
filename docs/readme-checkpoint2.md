C++ Computation Engine:

Built a shared library (libbudget.so) with five algorithms (Brute Force, DP, Greedy, Backtracking, Hybrid) for the subset sum problem.
Created a test executable (test_budget) that verifies all algorithms produce results for [10, 20, 30, 40] with budget 50.
Fixed CMake issues (include paths, Pybind11 configuration) to ensure successful builds.


Python Bindings:

Used Pybind11 to create budget_module.cpython-313-x86_64-linux-gnu.so, exposing C++ functions to Python.
Fixed ModuleNotFoundError by adding python/ to PYTHONPATH.
Tested bindings with test_budget.py, confirming all algorithms are callable from Python.


Current State:

The C++ library and Python bindings are functional, but dp.cpp has a bug (incorrect indices [1, 2] instead of [0, 3]).
FastAPI setup is incomplete, causing the uvicorn error.


Environment: Arch Linux, Python 3.13.7 (virtual env: ~/.venvs/global), CMake 4.1.2, GCC 15.2.1, Pybind11 3.0.1.
