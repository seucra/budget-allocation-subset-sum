from fastapi import FastAPI
from pydantic import BaseModel
import budget_module

app = FastAPI()

class BudgetRequest(BaseModel):
    costs: list[int]
    budget: int
    algorithm: str

@app.post("/solve/")
async def solve(request: BudgetRequest):
    algo_map = {
        "brute_force": budget_module.run_brute_force,
        "dp": budget_module.run_dp,
        "greedy": budget_module.run_greedy,
        "backtracking": budget_module.run_backtracking,
        "hybrid": budget_module.run_hybrid,
    }
    if request.algorithm not in algo_map:
        return {"error": "Invalid algorithm"}
    result = algo_map[request.algorithm](request.costs, request.budget)
    return {
        "total_cost": result.total_cost,
        "indices": result.indices,
        "execution_time_ms": result.execution_time_ms,
        "memory_used_mb": result.memory_used_mb
    }
