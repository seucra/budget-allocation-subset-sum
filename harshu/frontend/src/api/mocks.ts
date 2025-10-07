// frontend/src/api/mocks.ts
import type { IAlgorithmRun } from '../types';

// --- Interfaces for Analytics Benchmarks ---
export interface BenchmarkResult {
  input_size: number;
  brute_force_time: number; 
  dp_time: number;          
  greedy_time: number;      
  brute_force_mem: number;
  dp_mem: number;
  greedy_mem: number;
}

// Mock data demonstrating the different scalability profiles
export const mockBenchmarkData: BenchmarkResult[] = [
  { input_size: 10, brute_force_time: 0.1, dp_time: 1.5, greedy_time: 0.01, brute_force_mem: 0.5, dp_mem: 1.0, greedy_mem: 0.1 },
  { input_size: 15, brute_force_time: 3.2, dp_time: 3.5, greedy_time: 0.05, brute_force_mem: 1.2, dp_mem: 2.5, greedy_mem: 0.1 },
  { input_size: 20, brute_force_time: 100.0, dp_time: 5.0, greedy_time: 0.08, brute_force_mem: 2.0, dp_mem: 4.0, greedy_mem: 0.2 },
  { input_size: 25, brute_force_time: 3000.0, dp_time: 7.5, greedy_time: 0.12, brute_force_mem: 4.0, dp_mem: 6.0, greedy_mem: 0.2 },
  { input_size: 30, brute_force_time: 90000.0, dp_time: 10.0, greedy_time: 0.15, brute_force_mem: 8.0, dp_mem: 8.0, greedy_mem: 0.3 },
];

export const mockFetchBenchmarks = (): Promise<BenchmarkResult[]> => {
  return new Promise((resolve) => {
    // Simulate API call to fetch analytics snapshots
    setTimeout(() => resolve(mockBenchmarkData), 800);
  });
};

// --- Mock Data for History (Will be used in Step 5) ---
export const mockHistoryData: IAlgorithmRun[] = [
    {
      run_id: 'run-001',
      dataset_id: 'data-A',
      budget: 300,
      selected_indices: [0, 1, 3],
      total_cost: 240,
      execution_time_ms: 50.123,
      memory_used_mb: 1.2,
      status: 'exact',
      algorithm_name: 'Dynamic Programming',
      input_projects: [],
      created_at: new Date(Date.now() - 86400000).toISOString(), // 1 day ago
    },
    {
      run_id: 'run-002',
      dataset_id: 'data-B',
      budget: 500,
      selected_indices: [5, 6, 7, 8],
      total_cost: 485,
      execution_time_ms: 100.5,
      memory_used_mb: 2.5,
      status: 'approximate',
      algorithm_name: 'Hybrid',
      input_projects: [],
      created_at: new Date().toISOString(),
    },
];

export const mockFetchHistory = (): Promise<IAlgorithmRun[]> => {
  return new Promise((resolve) => {
    // Simulate network delay
    setTimeout(() => resolve(mockHistoryData), 500);
  });
};