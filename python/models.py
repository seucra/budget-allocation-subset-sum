from sqlalchemy import Column, Integer, String, Float
from sqlalchemy.types import JSON
from db import Base

class AlgorithmRun(Base):
    __tablename__ = "algorithm_runs"

    id = Column(Integer, primary_key=True, index=True)
    algorithm = Column(String, index=True)
    costs = Column(JSON)
    budget = Column(Integer)
    total_cost = Column(Integer)
    indices = Column(JSON)
    execution_time_ms = Column(Float)
    memory_used_mb = Column(Float)
