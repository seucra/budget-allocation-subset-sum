from models import ProjectSet
from db import init_db
import time

def placeholder_subset_sum(projects, budget):
    start_time = time.time()
    selected = []
    total_cost = 0
    for i, proj in enumerate(projects):
        if total_cost + proj["cost"] <= budget:
            selected.append(i)
            total_cost += proj["cost"]
    exec_time = time.time() - start_time
    return selected, total_cost, exec_time

if __name__ == "__main__":
    init_db()  # Create tables
    projects = [{"name": "Proj1", "cost": 100}, {"name": "Proj2", "cost": 200}, {"name": "Proj3", "cost": 150}]
    budget = 300
    indices, cost, time = placeholder_subset_sum(projects, budget)
    print(f"Selected indices: {indices}, Total cost: {cost}, Time: {time}")
