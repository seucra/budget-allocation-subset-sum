// frontend/src/pages/AnalyticsPage.tsx
import React from 'react';

const AnalyticsPage: React.FC = () => {
  return (
    <div className="container mx-auto p-4">
      <h1 className="text-3xl font-bold mb-6">Performance Analytics (Route: /analytics)</h1>
      <p className="mb-4">
        This dashboard visualizes performance metrics (time, memory, accuracy) fetched from the 
        backend's benchmarking data.
      </p>
      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        <div className="border p-4 h-96 flex items-center justify-center bg-gray-50">
          [Execution Time vs. Input Size Chart Component]
        </div>
        <div className="border p-4 h-96 flex items-center justify-center bg-gray-50">
          [Memory Usage vs. Input Size Chart Component]
        </div>
      </div>
    </div>
  );
};

export default AnalyticsPage;