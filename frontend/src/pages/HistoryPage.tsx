// frontend/src/pages/HistoryPage.tsx
import React, { useState, useEffect } from 'react';
import type { IAlgorithmRun } from '../types'; 
// START STEP 5: Import the mock fetch function from the centralized API mocks file
import { mockFetchHistory } from '../api/mocks';
// END STEP 5

// Helper Component for displaying the list row
interface RunRowProps {
  run: IAlgorithmRun;
  onSelect: (run: IAlgorithmRun) => void;
}

const RunRow: React.FC<RunRowProps> = ({ run, onSelect }) => {
  const date = new Date(run.created_at).toLocaleString();
  const statusColor = run.status === 'exact' ? 'text-green-600' : 'text-yellow-600';
  
  return (
    <tr 
      onClick={() => onSelect(run)} 
      className="cursor-pointer hover:bg-indigo-50 transition duration-150"
    >
      <td className="p-3 text-sm font-medium text-gray-900">{run.run_id}</td>
      <td className="p-3 text-sm text-gray-500">{run.algorithm_name}</td>
      <td className="p-3 text-sm font-mono">${run.total_cost.toFixed(0)} / ${run.budget.toFixed(0)}</td>
      <td className="p-3 text-sm font-medium" >
        <span className={statusColor}>{run.status.toUpperCase()}</span>
      </td>
      <td className="p-3 text-sm text-gray-500">{date}</td>
    </tr>
  );
};


const HistoryPage: React.FC = () => {
  const [history, setHistory] = useState<IAlgorithmRun[]>([]);
  const [selectedRun, setSelectedRun] = useState<IAlgorithmRun | null>(null);
  const [isLoading, setIsLoading] = useState<boolean>(true);

  useEffect(() => {
    // Fetch historical runs on component mount
    setIsLoading(true);
    // START STEP 5: Call the imported mock fetch function
    mockFetchHistory().then(data => {
      setHistory(data);
      setIsLoading(false);
      // Automatically select the most recent run for detail view
      if (data.length > 0) {
        setSelectedRun(data[0]); 
      }
    });
    // END STEP 5
  }, []);
  
  // Renders the detailed information of the selected run
  const RunDetail = () => {
    if (!selectedRun) return null;
    
    return (
      <div className="bg-white p-6 border rounded-lg shadow-md">
        <h3 className="text-xl font-bold mb-4">Details for Run: {selectedRun.run_id}</h3>
        <div className="grid grid-cols-2 gap-4 text-sm">
          <div>
            <p><strong>Algorithm:</strong> {selectedRun.algorithm_name}</p>
            <p><strong>Date:</strong> {new Date(selectedRun.created_at).toLocaleString()}</p>
            <p><strong>Total Cost:</strong> ${selectedRun.total_cost.toFixed(2)}</p>
            <p><strong>Budget:</strong> ${selectedRun.budget.toFixed(2)}</p>
          </div>
          <div>
            <p><strong>Execution Time:</strong> {selectedRun.execution_time_ms.toFixed(3)} ms</p>
            <p><strong>Memory Used:</strong> {selectedRun.memory_used_mb.toFixed(3)} MB</p>
            <p><strong>Projects Selected:</strong> {selectedRun.selected_indices.length}</p>
            <p><strong>Status:</strong> <span className={selectedRun.status === 'exact' ? 'text-green-600' : 'text-yellow-600'}>{selectedRun.status.toUpperCase()}</span></p>
          </div>
        </div>
        <p className="mt-4 text-xs font-mono break-words">
          <strong>Selected Indices:</strong> {selectedRun.selected_indices.join(', ')}
        </p>
      </div>
    );
  };
  

  return (
    <div className="container mx-auto p-6">
      <h1 className="text-4xl font-extrabold text-gray-800 mb-6">Run History Dashboard</h1>
      <p className="text-gray-600 mb-6">
        Review past execution results and performance metrics. This data is pulled from the 
        PostgreSQL <code>AlgorithmRun</code> table via the FastAPI backend.
      </p>

      <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
        
        {/* History List Panel */}
        <div className="lg:col-span-2 bg-gray-50 p-4 border rounded-lg shadow-md">
          <h2 className="text-2xl font-semibold mb-4">Historical Runs ({history.length})</h2>
          {isLoading ? (
            <div className="p-10 text-center text-gray-500">Loading history...</div>
          ) : history.length === 0 ? (
            <div className="p-10 text-center text-gray-500 border border-dashed rounded-lg">No historical runs found.</div>
          ) : (
            <div className="overflow-x-auto">
              <table className="min-w-full divide-y divide-gray-200">
                <thead className="bg-gray-200">
                  <tr>
                    <th className="p-3 text-left text-xs font-medium text-gray-600 uppercase tracking-wider">Run ID</th>
                    <th className="p-3 text-left text-xs font-medium text-gray-600 uppercase tracking-wider">Algorithm</th>
                    <th className="p-3 text-left text-xs font-medium text-gray-600 uppercase tracking-wider">Cost/Budget</th>
                    <th className="p-3 text-left text-xs font-medium text-gray-600 uppercase tracking-wider">Status</th>
                    <th className="p-3 text-left text-xs font-medium text-gray-600 uppercase tracking-wider">Date</th>
                  </tr>
                </thead>
                <tbody className="bg-white divide-y divide-gray-200">
                  {history.map(run => (
                    <RunRow key={run.run_id} run={run} onSelect={setSelectedRun} />
                  ))}
                </tbody>
              </table>
            </div>
          )}
        </div>

        {/* Detail Panel */}
        <div className="lg:col-span-1">
          <h2 className="text-2xl font-semibold mb-4">Run Details</h2>
          {selectedRun ? (
            <RunDetail />
          ) : (
            <div className="bg-white p-6 border rounded-lg shadow-md text-gray-500 text-center">
              Select a run from the list to view its detailed metrics.
            </div>
          )}
        </div>
      </div>
    </div>
  );
};

export default HistoryPage;