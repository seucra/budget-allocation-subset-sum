// frontend/src/pages/SolverPage.tsx
import React, { useState, useCallback } from 'react';
import type { IProject, IAlgorithmResult, ISolveRequest } from '../types'; // <-- CRITICAL FIX
import ProjectInputForm from '../components/input/ProjectInputForm';
import BudgetControl from '../components/input/BudgetControl';
import AlgorithmSelector from '../components/input/AlgorithmSelector';
import ResultCard from '../components/results/ResultCard';
import { runSolver } from '../api/solver';

// Initial state for demonstration purposes
const INITIAL_PROJECTS: IProject[] = [
  { id: '1', name: 'Project Alpha', cost: 120 },
  { id: '2', name: 'Project Beta', cost: 80 },
  { id: '3', name: 'Project Gamma', cost: 150 },
  { id: '4', name: 'Project Delta', cost: 40 },
];
const INITIAL_BUDGET = 300;

const SolverPage: React.FC = () => {
  // --- State Management ---
  const [projects, setProjects] = useState<IProject[]>(INITIAL_PROJECTS);
  const [budget, setBudget] = useState<number>(INITIAL_BUDGET);
  const [selectedAlgorithm, setSelectedAlgorithm] = useState<string>('Dynamic Programming');
  const [results, setResults] = useState<IAlgorithmResult[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(false);
  const [apiError, setApiError] = useState<string | null>(null);
  const [backendValidationErrors, setBackendValidationErrors] = useState<any>(null);


  // --- Core Logic: Handling API Call ---
  const handleSolve = useCallback(async () => {
    setApiError(null);
    setBackendValidationErrors(null);

    if (projects.length === 0) {
      setApiError("Please add projects to the dataset before running the solver.");
      return;
    }

    setIsLoading(true);
    setResults([]); // Clear previous results

    // Prepare the request body (aligning with ISolveRequest)
    const request: ISolveRequest = {
      projects: projects,
      budget: budget,
      // Pass the selected algorithm, or undefined if 'Auto-Select' is chosen
      algorithm: selectedAlgorithm === 'Auto-Select (Smart Solver)' ? undefined : selectedAlgorithm,
    };

    try {
      // Execute the API call (POST /solve/)
      const result = await runSolver(request);
      
      // Since the API returns one result (IAlgorithmRun), we adapt it to IAlgorithmResult array
      const AlgorithmResult: IAlgorithmResult= {
        selected_indices: result.selected_indices,
        total_cost: result.total_cost,
        execution_time_ms: result.execution_time_ms,
        memory_used_mb: result.memory_used_mb,
        status: result.status,
        algorithm_name: result.algorithm_name,
      };

      setResults([AlgorithmResult]); // Display the single result
      
    } catch (error: any) {
      // Robust Error Handling for C++ algorithm latency and validation errors
      
      // Check for structured validation errors (e.g., Pydantic errors from FastAPI)
      if (error.message.includes("API Error:") && error.message.includes("{")) {
          // Attempt to parse validation details if the API returned structured JSON errors
          setBackendValidationErrors(JSON.parse(error.message.split("API Error: ")[1]));
          setApiError("Validation Failed. Check input fields for specific errors.");
      } else {
          setApiError(error.message || "An unknown error occurred during computation.");
      }
      
    } finally {
      setIsLoading(false);
    }
  }, [projects, budget, selectedAlgorithm]); // Depend on state for memoization

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
            backendErrors={backendValidationErrors} 
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

          {/* Global API Error Display */}
          {apiError && (
              <div className="p-4 bg-red-100 border border-red-400 text-red-700 rounded-lg">
                  <p className="font-bold">Error:</p>
                  <p>{apiError}</p>
              </div>
          )}

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
              Running {selectedAlgorithm} on C++ Engine... (This may take a few seconds)
            </div>
          ) : (
            <div className="p-12 text-center text-gray-500 border border-dashed rounded-lg">
              Click 'Run Budget Solver' to execute the algorithm on your dataset.
            </div>
          )}
          
          {/* Visualization Area */}
          <div className="mt-8 pt-4 border-t">
            <h3 className="text-xl font-semibold mb-3">Visualization Area (Selected Subset)</h3>
            <div className="border p-4 h-32 flex items-center justify-center bg-gray-50 text-gray-500">
              Highlighting of selected projects and execution path goes here.
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default SolverPage;