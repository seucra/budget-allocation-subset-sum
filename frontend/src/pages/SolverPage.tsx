// frontend/src/pages/SolverPage.tsx
import React, { useState } from 'react';
import { IProject, IAlgorithmResult } from '../types';
import ProjectInputForm from '../components/input/ProjectInputForm';
import AlgorithmSelector from '../components/input/AlgorithmSelector';
import ResultCard from '../components/results/ResultCard';

// Mock API Call (Replace with actual Axios call later)
const mockSolveAPI = (projects: IProject[], budget: number, algorithm: string): Promise<IAlgorithmResult> => {
  return new Promise((resolve) => {
    const isDP = algorithm === 'Dynamic Programming';
    const isGreedy = algorithm === 'Greedy Heuristic';
    const isFailed = projects.length === 0 && budget === 0;

    // Simulate backend processing time (latency management is key here)
    setTimeout(() => {
      if (isFailed) {
        resolve({
          selected_indices: [],
          total_cost: 0,
          execution_time_ms: 10,
          memory_used_mb: 0.1,
          status: 'failed',
          algorithm_name: algorithm
        });
        return;
      }

      // Simulate a result structure for the given budget/projects
      const totalCost = Math.min(budget, 290);
      const indices = [0, 1, 3]; // Dummy indices for a result
      
      resolve({
        selected_indices: indices,
        total_cost: totalCost,
        execution_time_ms: isDP ? 50.123 : isGreedy ? 0.87 : 100.5,
        memory_used_mb: isDP ? 10.5 : isGreedy ? 0.01 : 1.2,
        status: isDP ? 'exact' : 'approximate',
        algorithm_name: algorithm
      });
    }, 1500); // 1.5 second delay
  });
};

const SolverPage: React.FC = () => {
  // --- State Management ---
  const [projects, setProjects] = useState<IProject[]>([
    { id: '1', name: 'Project Alpha', cost: 120 },
    { id: '2', name: 'Project Beta', cost: 80 },
    { id: '3', name: 'Project Gamma', cost: 150 },
    { id: '4', name: 'Project Delta', cost: 40 },
  ]);
  const [budget, setBudget] = useState<number>(300);
  const [selectedAlgorithm, setSelectedAlgorithm] = useState<string>('Dynamic Programming');
  const [results, setResults] = useState<IAlgorithmResult[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);

  // --- Core Logic ---
  const handleSolve = async () => {
    if (projects.length === 0) return alert("Please add projects first.");

    setIsLoading(true);
    setResults([]); // Clear previous results before running

    // In a production app, you would iterate over a list of algorithms 
    // to run side-by-side, but here we run only the selected one for simplicity.
    try {
      // API call to POST /solve/
      const result = await mockSolveAPI(projects, budget, selectedAlgorithm);
      setResults([result]); // Display the single result
    } catch (error) {
      console.error("Solver error:", error);
      // Implement robust error handling for API failures/timeouts.
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className="container mx-auto p-6">
      <h1 className="text-4xl font-extrabold text-gray-800 mb-6">Budget Allocation Solver</h1>

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
        {/* --- Left Panel: Input & Controls --- */}
        <div className="lg:col-span-1 space-y-8 p-4 border rounded-lg bg-gray-50 shadow-md">
          <h2 className="text-2xl font-semibold border-b pb-2">Input & Controls</h2>
          
          <BudgetControl budget={budget} setBudget={setBudget} />

          <ProjectInputForm 
            projects={projects} 
            setProjects={setProjects} 
            backendErrors={null} 
          />
          
          <AlgorithmSelector
            selectedAlgorithm={selectedAlgorithm}
            onSelect={setSelectedAlgorithm}
            onSolve={handleSolve}
            isLoading={isLoading}
          />
        </div>

        {/* --- Right Panel: Results & Visualization --- */}
        <div className="lg:col-span-2 space-y-6 p-4 border rounded-lg bg-white shadow-md">
          <h2 className="text-2xl font-semibold border-b pb-2">Algorithm Results & Comparison</h2>

          {/* Result Display Area */}
          {results.length > 0 ? (
            <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
              {results.map((result, index) => (
                <ResultCard key={index} result={result} budget={budget} />
              ))}
            </div>
          ) : isLoading ? (
            <div className="p-12 text-center text-gray-500">
              <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-indigo-600 mx-auto mb-3"></div>
              Running {selectedAlgorithm}... Please wait.
            </div>
          ) : (
            <div className="p-12 text-center text-gray-500 border border-dashed rounded-lg">
              Run an algorithm to view the selected project subset and performance metrics here.
            </div>
          )}
          
          {/* Optional Visualization Area */}
          <div className="mt-8 pt-4 border-t">
            <h3 className="text-xl font-semibold mb-3">Visualization Area</h3>
            <div className="border p-4 h-32 flex items-center justify-center bg-gray-50 text-gray-500">
              Graphical highlight of selected projects and execution path goes here.
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default SolverPage;