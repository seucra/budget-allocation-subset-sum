from fastapi import FastAPI, HTTPException, Depends
from pydantic import BaseModel
from sqlalchemy.orm import Session
from contextlib import asynccontextmanager
import budget_module
from db import SessionLocal, init_db
from models import AlgorithmRun

@asynccontextmanager
async def lifespan(app: FastAPI):
    init_db()
    yield

app = FastAPI(lifespan=lifespan)

class BudgetRequest(BaseModel):
    costs: list[int]
    budget: int
    algorithm: str

class CompareRequest(BaseModel):
    costs: list[int]
    budget: int

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.get("/health/")
async def health(db: Session = Depends(get_db)):
    try:
        db.execute("SELECT 1")
        return {"status": "healthy", "database": "connected"}
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Database error: {str(e)}")

@app.post("/solve/")
async def solve(request: BudgetRequest, db: Session = Depends(get_db)):
    algo_map = {
        "brute_force": budget_module.run_brute_force,
        "dp": budget_module.run_dp,
        "greedy": budget_module.run_greedy,
        "backtracking": budget_module.run_backtracking,
        "hybrid": budget_module.run_hybrid,
    }
    if request.algorithm not in algo_map:
        raise HTTPException(status_code=400, detail="Invalid algorithm")

    result = algo_map[request.algorithm](request.costs, request.budget)
    run = AlgorithmRun(
        algorithm=request.algorithm,
        costs=request.costs,
        budget=request.budget,
        total_cost=result.total_cost,
        indices=result.indices,
        execution_time_ms=result.execution_time_ms,
        memory_used_mb=result.memory_used_mb
    )
    db.add(run)
    db.commit()
    db.refresh(run)

    return {
        "run_id": run.id,
        "total_cost": result.total_cost,
        "indices": result.indices,
        "execution_time_ms": result.execution_time_ms,
        "memory_used_mb": result.memory_used_mb,
        "accuracy": result.total_cost / request.budget if request.budget > 0 else 0.0
    }

@app.get("/results/{run_id}")
async def get_result(run_id: int, db: Session = Depends(get_db)):
    run = db.query(AlgorithmRun).filter(AlgorithmRun.id == run_id).first()
    if not run:
        raise HTTPException(status_code=404, detail="Run not found")
    return {
        "run_id": run.id,
        "algorithm": run.algorithm,
        "costs": run.costs,
        "budget": run.budget,
        "total_cost": run.total_cost,
        "indices": run.indices,
        "execution_time_ms": run.execution_time_ms,
        "memory_used_mb": run.memory_used_mb,
        "accuracy": run.total_cost / run.budget if run.budget > 0 else 0.0
    }

@app.post("/compare/")
async def compare(request: CompareRequest, db: Session = Depends(get_db)):
    algo_map = {
        "brute_force": budget_module.run_brute_force,
        "dp": budget_module.run_dp,
        "greedy": budget_module.run_greedy,
        "backtracking": budget_module.run_backtracking,
        "hybrid": budget_module.run_hybrid,
    }
    results = []
    optimal_cost = max([sum(request.costs[i] for i in combo) 
                        for combo in [[i for i in range(len(request.costs)) 
                        if (mask & (1 << i)) > 0] for mask in range(1 << len(request.costs))] 
                        if sum([request.costs[i] for i in combo]) <= request.budget] + [0])

    for algo_name, algo_func in algo_map.items():
        result = algo_func(request.costs, request.budget)
        run = AlgorithmRun(
            algorithm=algo_name,
            costs=request.costs,
            budget=request.budget,
            total_cost=result.total_cost,
            indices=result.indices,
            execution_time_ms=result.execution_time_ms,
            memory_used_mb=result.memory_used_mb
        )
        db.add(run)
        accuracy = result.total_cost / optimal_cost if optimal_cost > 0 else 0.0
        results.append({
            "algorithm": algo_name,
            "total_cost": result.total_cost,
            "indices": result.indices,
            "execution_time_ms": result.execution_time_ms,
            "memory_used_mb": result.memory_used_mb,
            "accuracy": accuracy
        })
    db.commit()
    return results
