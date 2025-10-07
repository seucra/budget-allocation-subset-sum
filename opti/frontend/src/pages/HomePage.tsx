// frontend/src/pages/HomePage.tsx
import React from 'react';
import { Link } from 'react-router-dom';

const HomePage: React.FC = () => {
  return (
    <div className="container mx-auto p-8 max-w-4xl bg-white shadow-lg rounded-lg mt-10">

      {/* Header and Overview */}
      <h1 className="text-4xl font-extrabold text-gray-800 mb-4 border-b pb-2">
        Budget Allocation using Subset Sum Algorithms
      </h1>
      <p className="text-lg text-gray-600 mb-6">
        This project implements various algorithms (Dynamic Programming, Backtracking, Greedy, etc.) to solve
        budget allocation problems modeled as the **Subset Sum Problem**.
        It allows users to manage projects, assign metadata, and get optimal selections within a given budget, utilizing a
        high-performance C++ computation engine orchestrated by a Python FastAPI backend.
      </p>

      {/* Key Features Section */}
      <h2 className="text-2xl font-semibold text-gray-700 mt-6 mb-4">
        Key Features
      </h2>
      <ul className="list-disc list-inside space-y-2 text-gray-700 pl-4 mb-8">
        <li>
          **Interactive Project Management:** Add, remove, and edit projects with associated costs and optional metadata like priority and risk factor.
        </li>
        <li>
          **Algorithm Comparison:** Run multiple algorithms (Brute Force, DP, Backtracking, Greedy, Hybrid) side-by-side to compare results and performance metrics.
        </li>
        <li>
          **Performance Dashboard:** Display execution time and memory usage metrics for each algorithm run.
        </li>
        <li>
          **Visualization & Analytics:** Graphical representation of results and scalability benchmarks.
        </li>
        <li>
          **Robust Backend:** Utilizes C++ for computation and PostgreSQL for persistent storage of datasets and runs.
        </li>
      </ul>

      {/* Navigation */}
      <h2 className="text-2xl font-semibold text-gray-700 mt-6 mb-4">
        Navigate
      </h2>
      <div className="flex flex-col sm:flex-row space-y-4 sm:space-y-0 sm:space-x-4">
        <Link
          to="/solve"
          className="flex-1 bg-blue-600 text-white text-center py-3 px-6 rounded-lg font-bold hover:bg-blue-700 transition duration-150"
        >
          Go to Project Solver
        </Link>
        <Link
          to="/history"
          className="flex-1 bg-gray-200 text-gray-800 text-center py-3 px-6 rounded-lg font-bold hover:bg-gray-300 transition duration-150"
        >
          View Run History
        </Link>
        <Link
          to="/analytics"
          className="flex-1 bg-gray-200 text-gray-800 text-center py-3 px-6 rounded-lg font-bold hover:bg-gray-300 transition duration-150"
        >
          Performance Analytics
        </Link>
      </div>

    </div>
  );
};

export default HomePage;