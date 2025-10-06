// tests/SolverTests.cpp
#include "gtest/gtest.h"
#include "AlgorithmSelector/SolverFactory.h"
#include "DataModel/DataSet.h"
#include <vector>
#include <numeric>
#include <algorithm>

// Fixture for common test data
class SolverTest : public ::testing::Test {
protected:
    DataSet data;
    void SetUp() override {
        data.numbers = {3, 34, 4, 12, 5, 2};
    }

    // Helper to verify the sum of a subset
    void verify_subset_sum(int target, const std::vector<int>& subset) {
        int sum = std::accumulate(subset.begin(), subset.end(), 0);
        ASSERT_EQ(sum, target);
    }
};

// --- Test the DP Solver ---
TEST_F(SolverTest, DPSolver_FindsSolution) {
    data.target_sum = 9;
    auto solver = SolverFactory::createSolver("dp");
    auto result = solver->solve(data);
    
    ASSERT_TRUE(result.solution_exists);
    ASSERT_FALSE(result.subsets.empty());
    verify_subset_sum(data.target_sum, result.subsets[0]);
}

TEST_F(SolverTest, DPSolver_NoSolution) {
    data.target_sum = 30;
    auto solver = SolverFactory::createSolver("dp");
    auto result = solver->solve(data);
    ASSERT_FALSE(result.solution_exists);
}

// --- Test the Backtracking Solver ---
TEST_F(SolverTest, BacktrackingSolver_FindsSolution) {
    data.target_sum = 9;
    auto solver = SolverFactory::createSolver("backtrack");
    auto result = solver->solve(data);
    
    ASSERT_TRUE(result.solution_exists);
    ASSERT_FALSE(result.subsets.empty());
    verify_subset_sum(data.target_sum, result.subsets[0]);
}

TEST_F(SolverTest, BacktrackingSolver_NoSolution) {
    data.target_sum = 30;
    auto solver = SolverFactory::createSolver("backtrack");
    auto result = solver->solve(data);
    ASSERT_FALSE(result.solution_exists);
}

TEST_F(SolverTest, EdgeCase_EmptySet) {
    data.numbers = {};
    data.target_sum = 5;
    auto solver_dp = SolverFactory::createSolver("dp");
    auto result_dp = solver_dp->solve(data);
    ASSERT_FALSE(result_dp.solution_exists);

    auto solver_bt = SolverFactory::createSolver("backtrack");
    auto result_bt = solver_bt->solve(data);
    ASSERT_FALSE(result_bt.solution_exists);
}

TEST_F(SolverTest, EdgeCase_TargetIsZero) {
    data.target_sum = 0;
    auto solver = SolverFactory::createSolver("dp");
    auto result = solver->solve(data);
    ASSERT_TRUE(result.solution_exists);
    ASSERT_EQ(result.subsets.size(), 1);
    ASSERT_TRUE(result.subsets[0].empty());
}
