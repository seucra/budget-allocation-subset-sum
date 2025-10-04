// frontend/src/pages/AnalyticsPage.tsx
import React, { useState, useEffect } from 'react';
import ExecutionTimeChart from '../components/charts/ExecutionTimeChart';
import MemoryUsageChart from '../components/charts/MemoryUsageChart';
// START STEP 4: Import mock functions and types from the new mock file
// NOTE: If the path below fails, ensure the mocks.ts file is correctly saved in src/api/
import type { BenchmarkResult } from '../api/mocks.ts';
import { mockFetchBenchmarks } from '../api/mocks.ts';
// END STEP 4

const AnalyticsPage: React.FC = () => {
  // START STEP 4: Use BenchmarkResult interface from the new module
  const [benchmarkData, setBenchmarkData] = useState<BenchmarkResult[]>([]);
  // END STEP 4
  const [isLoading, setIsLoading] = useState<boolean>(true);

  useEffect(() => {
    setIsLoading(true);
    // In production, this would be an Axios call to the FastAPI GET /benchmark/ endpoint
    // START STEP 4: Call the imported mock fetch function
    mockFetchBenchmarks().then((data: BenchmarkResult[]) => { // <-- FIX: Added type annotation for 'data'
      setBenchmarkData(data);
      setIsLoading(false);
    });
    // END STEP 4
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