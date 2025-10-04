#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "brute_force.h"
#include "greedy.h"

namespace py = pybind11;

PYBIND11_MODULE(budget_module, m) {
    py::class_<Result>(m, "Result")
        .def_readwrite("indices", &Result::indices)
        .def_readwrite("total_cost", &Result::total_cost)
        .def_readwrite("execution_time", &Result::execution_time);

    m.def("brute_force_subset_sum", &brute_force_subset_sum, "Brute force subset sum");
    m.def("greedy_subset_sum", &greedy_subset_sum, "Greedy subset sum");
}
