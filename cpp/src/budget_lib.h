#ifndef BUDGET_LIB_H
#define BUDGET_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

struct CResult {
    int* indices;      // Selected project indices (allocated with malloc)
    int count;         // Number of selected indices
    int total_cost;    // Total cost of selected projects
    double exec_time;  // Execution time in milliseconds
};

CResult run_brute_force_c(const int* costs, int n, int budget);
CResult run_dp_c(const int* costs, int n, int budget);
CResult run_greedy_c(const int* costs, int n, int budget);
CResult run_backtracking_c(const int* costs, int n, int budget);
CResult run_hybrid_c(const int* costs, int n, int budget);

void free_result(CResult result);

#ifdef __cplusplus
}
#endif

#endif // BUDGET_LIB_H

