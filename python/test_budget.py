import budget_module

def print_result(res, algo_name):
    print(f"Algorithm: {algo_name}")
    print(f"Total Cost: {res.total_cost}")
    print(f"Execution Time: {res.execution_time_ms}ms")
    print(f"Memory Used: {res.memory_used_mb}MB")
    print(f"Selected Indices: {res.indices}\n")

if __name__ == "__main__":
    costs = [10, 20, 30, 40]
    budget = 50

    for algo in [
        ("Brute Force", budget_module.run_brute_force),
        ("Dynamic Programming", budget_module.run_dp),
        ("Greedy", budget_module.run_greedy),
        ("Backtracking", budget_module.run_backtracking),
        ("Hybrid", budget_module.run_hybrid),
    ]:
        res = algo[1](costs, budget)
        print_result(res, algo[0])
