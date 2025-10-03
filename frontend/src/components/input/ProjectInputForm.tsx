// frontend/src/components/input/ProjectInputForm.tsx
import React from 'react';
import { IProject } from '../../types';

interface ProjectInputFormProps {
  projects: IProject[];
  setProjects: (projects: IProject[]) => void;
  // For validation and error handling
  backendErrors: any;
}

const ProjectInputForm: React.FC<ProjectInputFormProps> = ({ projects, setProjects, backendErrors }) => {
  // This component needs to handle adding/editing/deleting projects.
  // It should use React Hook Form for validation.
  // For large inputs (up to 1000 projects), a virtualized list is required for performance.
  
  return (
    <div className="space-y-4">
      <h3 className="text-lg font-semibold border-b pb-2">Projects ({projects.length})</h3>
      {/* Project List: Placeholder for Virtualized List */}
      <div className="h-48 overflow-y-scroll border p-2 bg-white">
        {projects.map(p => (
          <div key={p.id} className="flex justify-between items-center py-1 border-b text-sm">
            <span>{p.name || `Project ${p.id}`}</span>
            <span className="font-mono">${p.cost.toFixed(0)}</span>
          </div>
        ))}
        {projects.length === 0 && <p className="text-gray-500 italic">Add a project to begin.</p>}
      </div>
      {/* Input row for new project */}
      <button className="w-full bg-green-500 text-white py-2 rounded hover:bg-green-600 transition">
        + Add New Project
      </button>
      {/* Display Pydantic validation errors here */}
      {backendErrors && <p className="text-red-500 text-sm mt-2">Input validation errors from API.</p>}
    </div>
  );
};

export default ProjectInputForm;