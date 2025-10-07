// frontend/src/types.ts

// 1. Project Entity (Mirrors Project DB Model)
export interface IProject {
  id: string; // Use string UUID or temporary ID for frontend management
  name: string;
  cost: number;
  // Optional metadata from the DB/API (JSONB field on the backend)
  metadata?: {
    priority?: number;
    risk_factor?: number;
    [key: string]: any;
  };
}

// 2. Algorithm Result (Mirrors C++ common.h Result struct + FastAPI additions)
export interface IAlgorithmResult {
  selected_indices: number[];
  total_cost: number;
  execution_time_ms: number;
  memory_used_mb: number;
  status: 'exact' | 'approximate' | 'failed' | 'running';
  algorithm_name: string;
}

// 3. Full Algorithm Run Data (Mirrors AlgorithmRun DB Model)
export interface IAlgorithmRun extends IAlgorithmResult {
  run_id: string; // ID to fetch historical results (GET /results/{run_id}/)
  dataset_id: string;
  budget: number;
  // The input list of projects used for this specific run
  input_projects: IProject[];
  created_at: string;
}

// 4. API Request Body for POST /solve/
export interface ISolveRequest {
  projects: IProject[];
  budget: number;
  algorithm?: string; // Optional override; defaults to backend's Smart Solver
}