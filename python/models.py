from sqlalchemy import Column, Integer, String, Float, JSON
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class ProjectSet(Base):
    __tablename__ = "project_sets"
    id = Column(Integer, primary_key=True, index=True)
    name = Column(String, index=True)
    projects = Column(JSON)  # List of projects: [{"name": str, "cost": float}, ...]
    budget = Column(Float)

class AlgorithmRun(Base):
    __tablename__ = "algorithm_runs"
    id = Column(Integer, primary_key=True, index=True)
    project_set_id = Column(Integer)
    algorithm = Column(String)  # e.g., "brute_force", "dp"
    result = Column(JSON)  # Selected project indices
    total_cost = Column(Float)
    execution_time = Column(Float)
