from fastapi import FastAPI, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.orm import Session
from typing import List
from db import get_db
from models import ProjectSet, AlgorithmRun
import budget_module  # Import C++ module

app = FastAPI()

class Project(BaseModel):
    name: str
    cost: float

class BudgetRequest(BaseModel):
    projects: List[Project]
    budget: float
    algorithm: str = "greedy"  # Default to greedy

def run_algorithm(algorithm: str, projects: List[dict], budget: float):
    costs = [proj["cost"] for proj in projects]
    if algorithm == "brute_force":
        return budget_module.brute_force_subset_sum(costs, budget)
    elif algorithm == "greedy":
        return budget_module.greedy_subset_sum(costs, budget)
    else:
        raise ValueError("Unknown algorithm")

@app.post("/solve")
def solve_budget(request: BudgetRequest, db: Session = Depends(get_db)):
    project_set = ProjectSet(
        name="Test Set",
        projects=[proj.model_dump() for proj in request.projects],
        budget=request.budget
    )
    db.add(project_set)
    db.commit()
    db.refresh(project_set)

    # Run C++ algorithm
    result = run_algorithm(request.algorithm, project_set.projects, project_set.budget)

    run = AlgorithmRun(
        project_set_id=project_set.id,
        algorithm=request.algorithm,
        result=result.indices,
        total_cost=result.total_cost,
        execution_time=result.execution_time
    )
    db.add(run)
    db.commit()

    return {
        "project_set_id": project_set.id,
        "selected_indices": result.indices,
        "total_cost": result.total_cost,
        "execution_time": result.execution_time
    }
