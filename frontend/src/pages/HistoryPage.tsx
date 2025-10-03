// frontend/src/pages/HistoryPage.tsx
import React from 'react';

const HistoryPage: React.FC = () => {
  return (
    <div className="container mx-auto p-4">
      <h1 className="text-3xl font-bold mb-6">Run History (Route: /history)</h1>
      <p className="mb-4">
        This page will fetch and display a list of historical algorithm runs stored via the 
        `GET /results/{run_id}/` backend endpoint.
      </p>
      {/* Component: RunList, HistoryDetailViewer */}
      <div className="border p-4 h-64 flex items-center justify-center bg-gray-50">
        [History List and Detail Viewer Components will go here]
      </div>
    </div>
  );
};

export default HistoryPage;