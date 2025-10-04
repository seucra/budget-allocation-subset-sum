-- Already handled by SQLAlchemy's Base.metadata.create_all in db.py
-- This file can be empty or used for manual setup if needed

CREATE TABLE project_sets (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    projects JSONB NOT NULL,
    budget FLOAT NOT NULL
);

CREATE TABLE algorithm_runs (
    id SERIAL PRIMARY KEY,
    project_set_id INTEGER NOT NULL,
    algorithm VARCHAR(50) NOT NULL,
    result JSONB NOT NULL,
    total_cost FLOAT NOT NULL,
    execution_time FLOAT NOT NULL
);

CREATE INDEX idx_project_sets_name ON project_sets (name);
