// algorithms/greedy.cpp
#include "greedy.h"
#include <algorithm>
#include <chrono>

Result run_greedy(const std::vector<int>& costs, int budget) {
    auto start = std::chrono::high_resolution_clock::now();

    int n = (int)costs.size();
    std::vector<std::pair<int,int>> order;
    order.reserve(n);
    for (int i = 0; i < n; ++i) order.emplace_back(costs[i], i);

    // Simple greedy: sort ascending by cost
    std::sort(order.begin(), order.end());

    std::vector<int> selected;
    int sum = 0;
    for (auto &p : order) {
        if (sum + p.first <= budget) {
            sum += p.first;
            selected.push_back(p.second);
        } else {
            continue;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return {selected, sum, dur.count(), 0.0};
}

