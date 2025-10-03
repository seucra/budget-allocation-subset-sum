#ifndef COMMON_H
#define COMMON_H

#include <vector>

struct Result {
    std::vector<int> selected_indices;
    int total_cost;
    double execution_time_ms;
    double memory_used_mb; // For future expansion
};

#endif // COMMON_H

