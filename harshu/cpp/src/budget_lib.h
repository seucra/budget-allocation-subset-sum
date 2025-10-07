#ifndef BUDGET_LIB_H
#define BUDGET_LIB_H

#include "common.h"
#include "brute_force.h"
#include "dp.h"
#include "backtracking.h"
#include "greedy.h"
#include "hybrid.h"

// Optionally, export functions with C linkage for easier Python binding later

#ifdef __cplusplus
extern "C" {
#endif

Result run_brute_force(const std::vector<int>& costs, int budget);
Result run_dp(const std::vector<int>& costs, int budget);
Result run_backtracking(const std::vector<int>& costs, int budget);
Result run_greedy(const std::vector<int>& costs, int budget);
Result run_hybrid(const std::vector<int>& costs, int budget);

#ifdef __cplusplus
}
#endif

#endif // BUDGET_LIB_H

