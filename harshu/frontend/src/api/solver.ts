// frontend/src/api/solver.ts
import axios from 'axios';
import type { ISolveRequest, IAlgorithmResult } from '../types';

const API_BASE_URL = 'http://localhost:8000/api'; 

export const runSolver = async (request: ISolveRequest): Promise<IAlgorithmResult> => {
  try {
    const response = await axios.post(`${API_BASE_URL}/solve/`, request, {
      headers: {
        'Content-Type': 'application/json',
      },
      timeout: 30000, 
    });
    
    return response.data;
  } catch (error: any) {
    if (error.response) {
      const errorMessage = error.response.data?.detail || 
                          `API Error: ${JSON.stringify(error.response.data)}`;
      throw new Error(errorMessage);
    } else if (error.request) {
      throw new Error('Network error: Could not reach the backend server at ' + API_BASE_URL);
    } else {
      throw new Error(error.message || 'Unknown error occurred');
    }
  }
};

// New API call for history page
export const fetchHistory = async (): Promise<IAlgorithmResult[]> => {
  try {
    const response = await axios.get(`${API_BASE_URL}/history/`);
    return response.data;
  } catch (error: any) {
    console.error("Error fetching history:", error);
    throw new Error("Could not fetch historical runs.");
  }
};