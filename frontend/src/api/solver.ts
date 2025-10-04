import axios from 'axios';
import type { ISolveRequest, IAlgorithmResult } from '../types';

// Configure base URL for your FastAPI backend
const API_BASE_URL = 'http://localhost:8000/api'; // Adjust port as needed

export const runSolver = async (request: ISolveRequest): Promise<IAlgorithmResult> => {
  try {
    const response = await axios.post(`${API_BASE_URL}/solve/`, request, {
      headers: {
        'Content-Type': 'application/json',
      },
      timeout: 30000, // 30 second timeout for C++ computation
    });
    
    return response.data;
  } catch (error: any) {
    if (error.response) {
      // Backend returned error response (4xx, 5xx)
      const errorMessage = error.response.data?.detail || 
                          `API Error: ${JSON.stringify(error.response.data)}`;
      throw new Error(errorMessage);
    } else if (error.request) {
      // Network error - no response received
      throw new Error('Network error: Could not reach the backend server');
    } else {
      // Other errors
      throw new Error(error.message || 'Unknown error occurred');
    }
  }
};