// frontend/src/components/input/BudgetControl.tsx
import React from 'react';

interface BudgetControlProps {
  budget: number;
  setBudget: (budget: number) => void;
}

const BudgetControl: React.FC<BudgetControlProps> = ({ budget, setBudget }) => {
  return (
    <div className="space-y-2 p-4 border rounded-lg bg-white shadow-sm">
      <label htmlFor="budget-input" className="block text-sm font-medium text-gray-700">
        Total Available Budget ($)
      </label>
      <input
        id="budget-input"
        type="number"
        min="0"
        value={budget.toFixed(0)}
        onChange={(e) => {
          // Ensure input is a non-negative number
          const value = Math.max(0, parseInt(e.target.value) || 0);
          setBudget(value);
        }}
        placeholder="e.g., 500"
        className="w-full p-2 border border-gray-300 rounded-md focus:ring-indigo-500 focus:border-indigo-500"
      />
      <p className="text-xs text-gray-500">Set the total capital constraint for project selection.</p>
    </div>
  );
};

export default BudgetControl;