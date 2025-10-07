#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/budget_lib.h"

namespace py = pybind11;

PYBIND11_MODULE(budget_module, m) {
    py::class_<Result>(m, "Result")
        .def(py::init<>())
        .def_readwrite("indices", &Result::indices)
        .def_readwrite("total_cost", &Result::total_cost)
        .def_readwrite("execution_time_ms", &Result::execution_time_ms)
        .def_readwrite("memory_used_mb", &Result::memory_used_mb);

    m.def("run_brute_force", &run_brute_force, "Run brute force algorithm");
    m.def("run_dp", &run_dp, "Run dynamic programming algorithm");
    m.def("run_greedy", &run_greedy, "Run greedy algorithm");
    m.def("run_backtracking", &run_backtracking, "Run backtracking algorithm");
    m.def("run_hybrid", &run_hybrid, "Run hybrid algorithm");
}
