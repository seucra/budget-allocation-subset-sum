// frontend/src/components/results/ResultCard.tsx
import React from 'react';
import { IAlgorithmResult } from '../../types';

interface ResultCardProps {
  result: IAlgorithmResult;
  budget: number;
}

const ResultCard: React.FC<ResultCardProps> = ({ result, budget }) => {
  const isExact = result.status === 'exact';
  const statusColor = isExact ? 'text-green-600' : result.status === 'approximate' ? 'text-yellow-600' : 'text-red-600';
  
  // This card displays the final metrics from the backend.
  
  return (
    <div className="border rounded-lg p-4 shadow-md bg-white">
      <h3 className="text-xl font-bold mb-3 border-b pb-2 flex justify-between items-center">
        {result.algorithm_name}
        <span className={`text-sm font-semibold ${statusColor}`}>
          {result.status.toUpperCase()}
        </span>
      </h3>
      <div className="space-y-2 text-sm">
        <p><strong>Budget Used:</strong> ${result.total_cost.toFixed(2)} / ${budget.toFixed(2)}</p>
        <p><strong>Unused Budget:</strong> ${(budget - result.total_cost).toFixed(2)}</p>
        <p><strong>Execution Time:</strong> {result.execution_time_ms.toFixed(3)} ms</p>
        <p><strong>Memory Used:</strong> {result.memory_used_mb.toFixed(3)} MB</p>
        <p><strong>Projects Selected:</strong> {result.selected_indices.length} item(s)</p>
        <p className="font-mono text-xs overflow-x-auto break-words">
          Indices: {result.selected_indices.join(', ')}
        </p>
      </div>
    </div>
  );
};

export default ResultCard;