from fastapi import FastAPI, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy.orm import Session
from typing import List
from db import get_db
from models import ProjectSet, AlgorithmRun
import time

app = FastAPI()

# Pydantic models for input validation
class Project(BaseModel):
    name: str
    cost: float

class BudgetRequest(BaseModel):
    projects: List[Project]
    budget: float
    algorithm: str = "placeholder"

# Placeholder subset sum algorithm (to be replaced with C++ later)
def placeholder_subset_sum(projects: List[dict], budget: float) -> tuple:
    start_time = time.time()
    selected = []
    total_cost = 0
    for i, proj in enumerate(projects):
        if total_cost + proj["cost"] <= budget:
            selected.append(i)
            total_cost += proj["cost"]
    exec_time = time.time() - start_time
    return selected, total_cost, exec_time

@app.post("/solve")
def solve_budget(request: BudgetRequest, db: Session = Depends(get_db)):
    # Save project set
    project_set = ProjectSet(
        name="Test Set",
        projects=[proj.dict() for proj in request.projects],
        budget=request.budget
    )
    db.add(project_set)
    db.commit()
    db.refresh(project_set)

    # Run placeholder algorithm
    selected_indices, total_cost, exec_time = placeholder_subset_sum(
        project_set.projects, project_set.budget
    )

    # Save result
    run = AlgorithmRun(
        project_set_id=project_set.id,
        algorithm=request.algorithm,
        result=selected_indices,
        total_cost=total_cost,
        execution_time=exec_time
    )
    db.add(run)
    db.commit()

    return {
        "project_set_id": project_set.id,
        "selected_indices": selected_indices,
        "total_cost": total_cost,
        "execution_time": exec_time
    }
