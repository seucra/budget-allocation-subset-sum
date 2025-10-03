// frontend/src/api/solver.ts
import axios, { AxiosInstance } from 'axios';
import { IProject, IAlgorithmRun, ISolveRequest } from '../types';

// Define the base URL for the FastAPI backend.
// In a production environment, this should be an environment variable.
const API_BASE_URL = 'http://127.0.0.1:8000'; 

const api: AxiosInstance = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
  },
});

/**
 * Executes the Subset Sum solver on the backend.
 * Calls the core API endpoint that orchestrates the C++ algorithm execution.
 * * @param request ISolveRequest containing projects, budget, and selected algorithm.
 * @returns A promise resolving to the final algorithm run result.
 */
export const runSolver = async (request: ISolveRequest): Promise<IAlgorithmRun> => {
  // Matches the POST /solve/ endpoint
  try {
    const response = await api.post<IAlgorithmRun>('/solve/', request);
    return response.data;
  } catch (error) {
    // Crucial for managing latency and error feedback from the long-running C++ engine
    if (axios.isAxiosError(error) && error.response) {
      // Handle Pydantic validation errors or API execution failures
      throw new Error(`API Error: ${error.response.data.detail || 'Solver execution failed.'}`);
    }
    throw new Error('Network or unexpected error occurred during solve request.');
  }
};

/**
 * Fetches the history of a specific run ID.
 * Matches the GET /results/{run_id}/ endpoint
 */
export const getRunHistory = async (runId: string): Promise<IAlgorithmRun> => {
  try {
    const response = await api.get<IAlgorithmRun>(`/results/${runId}/`);
    return response.data;
  } catch (error) {
    throw new Error('Failed to fetch run history.');
  }
};

/**
 * Saves or updates a ProjectSet.
 * Matches the POST/GET /datasets/ endpoint
 */
export const saveProjectSet = async (projects: IProject[], budget: number): Promise<{ dataset_id: string }> => {
  try {
    const response = await api.post('/datasets/', { projects, budget });
    return response.data;
  } catch (error) {
    throw new Error('Failed to save project set.');
  }
};

// You will also add functions for fetching benchmark data (GET /benchmark/) here later.