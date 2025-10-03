#include "budget_lib_cpp.h"
#include "budget_lib.h"
#include <cstdlib>   // for malloc/free
#include <cstring>   // for memcpy
#include <vector>

// Helper: convert Result to CResult
static CResult to_c_result(const Result& res) {
    CResult c_res;
    c_res.count = static_cast<int>(res.indices.size());
    c_res.total_cost = res.total_cost;
    c_res.exec_time = res.execution_time_ms;
    if (c_res.count > 0) {
        c_res.indices = (int*)malloc(sizeof(int) * c_res.count);
        std::memcpy(c_res.indices, res.indices.data(), sizeof(int) * c_res.count);
    } else {
        c_res.indices = nullptr;
    }
    return c_res;
}

extern "C" {

CResult run_brute_force_c(const int* costs, int n, int budget) {
    std::vector<int> vec_costs(costs, costs + n);
    Result res = run_brute_force(vec_costs, budget);
    return to_c_result(res);
}

CResult run_dp_c(const int* costs, int n, int budget) {
    std::vector<int> vec_costs(costs, costs + n);
    Result res = run_dp(vec_costs, budget);
    return to_c_result(res);
}

CResult run_greedy_c(const int* costs, int n, int budget) {
    std::vector<int> vec_costs(costs, costs + n);
    Result res = run_greedy(vec_costs, budget);
    return to_c_result(res);
}

CResult run_backtracking_c(const int* costs, int n, int budget) {
    std::vector<int> vec_costs(costs, costs + n);
    Result res = run_backtracking(vec_costs, budget);
    return to_c_result(res);
}

CResult run_hybrid_c(const int* costs, int n, int budget) {
    std::vector<int> vec_costs(costs, costs + n);
    Result res = run_hybrid(vec_costs, budget);
    return to_c_result(res);
}

void free_result(CResult result) {
    if (result.indices != nullptr) {
        free(result.indices);
    }
}

} // extern "C"

