// frontend/src/components/input/AlgorithmSelector.tsx
import React from 'react';

interface AlgorithmSelectorProps {
  selectedAlgorithm: string;
  onSelect: (algo: string) => void;
  onSolve: () => void;
  isLoading: boolean;
}

const ALGORITHMS = [
  'Auto-Select (Smart Solver)',
  'Brute Force', 
  'Dynamic Programming', 
  'Backtracking', 
  'Greedy Heuristic', 
  'Hybrid'
];

const AlgorithmSelector: React.FC<AlgorithmSelectorProps> = ({ selectedAlgorithm, onSelect, onSolve, isLoading }) => {
  // This component provides the dropdown/toggle and the run button.
  
  return (
    <div className="space-y-4">
      <h3 className="text-lg font-semibold">Algorithm Selection</h3>
      <select 
        value={selectedAlgorithm} 
        onChange={(e) => onSelect(e.target.value)}
        className="block w-full p-2 border border-gray-300 rounded-md"
        disabled={isLoading}
      >
        {ALGORITHMS.map(algo => (
          <option key={algo} value={algo}>{algo}</option>
        ))}
      </select>
      <button 
        onClick={onSolve} 
        disabled={isLoading}
        className={`w-full py-3 rounded-lg font-bold transition ${
          isLoading 
            ? 'bg-yellow-500 text-gray-800 cursor-not-allowed' 
            : 'bg-indigo-600 text-white hover:bg-indigo-700'
        }`}
      >
        {isLoading ? 'Running Algorithm...' : 'Run Budget Solver (POST /solve/)'}
      </button>
      {isLoading && (
        <p className="text-sm text-yellow-600 mt-2">
          Computation is running on the high-performance C++ engine. A non-blocking UI is essential here!
        </p>
      )}
    </div>
  );
};

export default AlgorithmSelector;