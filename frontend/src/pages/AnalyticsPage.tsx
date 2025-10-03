// frontend/src/pages/AnalyticsPage.tsx
import React, { useState, useEffect } from 'react';
import ExecutionTimeChart from '../components/charts/ExecutionTimeChart';
import MemoryUsageChart from '../components/charts/MemoryUsageChart';

// --- MOCK API DATA AND FUNCTION ---
// Simulates fetching benchmark data from the GET /benchmark/ endpoint
interface BenchmarkResult {
  input_size: number;
  brute_force_time: number; 
  dp_time: number;          
  greedy_time: number;      
  brute_force_mem: number;
  dp_mem: number;
  greedy_mem: number;
}

// Mock data demonstrating the different scalability profiles:
// Brute Force: Time increases exponentially (O(2^N))
// DP: Time increases polynomially (O(N*W)) and requires space
// Greedy: Time increases minimally (O(N log N)) and requires minimal space
const mockBenchmarkData: BenchmarkResult[] = [
  { input_size: 10, brute_force_time: 0.1, dp_time: 1.5, greedy_time: 0.01, brute_force_mem: 0.5, dp_mem: 1.0, greedy_mem: 0.1 },
  { input_size: 15, brute_force_time: 3.2, dp_time: 3.5, greedy_time: 0.05, brute_force_mem: 1.2, dp_mem: 2.5, greedy_mem: 0.1 },
  { input_size: 20, brute_force_time: 100.0, dp_time: 5.0, greedy_time: 0.08, brute_force_mem: 2.0, dp_mem: 4.0, greedy_mem: 0.2 },
  { input_size: 25, brute_force_time: 3000.0, dp_time: 7.5, greedy_time: 0.12, brute_force_mem: 4.0, dp_mem: 6.0, greedy_mem: 0.2 },
  { input_size: 30, brute_force_time: 90000.0, dp_time: 10.0, greedy_time: 0.15, brute_force_mem: 8.0, dp_mem: 8.0, greedy_mem: 0.3 },
];

const mockFetchBenchmarks = (): Promise<BenchmarkResult[]> => {
  return new Promise((resolve) => {
    // Simulate API call to fetch analytics snapshots
    setTimeout(() => resolve(mockBenchmarkData), 800);
  });
};
// --- END MOCK ---

const AnalyticsPage: React.FC = () => {
  const [benchmarkData, setBenchmarkData] = useState<BenchmarkResult[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(true);

  useEffect(() => {
    setIsLoading(true);
    // In production, this would be an Axios call to the FastAPI GET /benchmark/ endpoint
    mockFetchBenchmarks().then(data => {
      setBenchmarkData(data);
      setIsLoading(false);
    });
  }, []);

  return (
    <div className="container mx-auto p-6">
      <h1 className="text-4xl font-extrabold text-gray-800 mb-6">Performance Analytics Dashboard</h1>
      <p className="text-gray-600 mb-8">
        Visualization of algorithm scalability and resource consumption using backend profiling data.
      </p>

      {isLoading ? (
        <div className="p-12 text-center text-gray-500">
          <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-indigo-600 mx-auto mb-3"></div>
          Fetching benchmark data...
        </div>
      ) : (
        <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
          
          {/* Execution Time Chart */}
          <div className="bg-white p-6 border rounded-lg shadow-md h-[400px]">
            {benchmarkData.length > 0 ? (
              <ExecutionTimeChart data={benchmarkData} />
            ) : (
              <p className="text-center text-gray-500 pt-10">No execution time data available.</p>
            )}
          </div>

          {/* Memory Usage Chart */}
          <div className="bg-white p-6 border rounded-lg shadow-md h-[400px]">
            {benchmarkData.length > 0 ? (
              <MemoryUsageChart data={benchmarkData} />
            ) : (
              <p className="text-center text-gray-500 pt-10">No memory usage data available.</p>
            )}
          </div>
          
          {/* Accuracy/Status Panel */}
          <div className="lg:col-span-2 bg-white p-6 border rounded-lg shadow-md">
            <h3 className="text-2xl font-semibold mb-3">Algorithm Accuracy Rates</h3>
            <p className="text-gray-600">
                This panel shows the percentage of runs where heuristic algorithms (Greedy, Hybrid) achieved an **exact match** versus an **approximate result**.
            </p>
            <div className="mt-4 grid grid-cols-2 gap-4">
                <div className="p-3 bg-indigo-50 rounded-lg">
                    <p className="text-sm font-medium">Greedy Heuristic Exact Match Rate:</p>
                    <p className="text-xl font-bold text-indigo-700">~75%</p>
                </div>
                <div className="p-3 bg-green-50 rounded-lg">
                    <p className="text-sm font-medium">Hybrid Algorithm Exact Match Rate:</p>
                    <p className="text-xl font-bold text-green-700">~95%</p>
                </div>
            </div>
          </div>
        </div>
      )}
    </div>
  );
};

export default AnalyticsPage;