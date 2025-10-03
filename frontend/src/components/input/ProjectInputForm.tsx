// frontend/src/components/input/ProjectInputForm.tsx
import React, { useState } from 'react';
import { IProject } from '../../types';

interface ProjectInputFormProps {
  projects: IProject[];
  setProjects: (projects: IProject[]) => void;
  // For validation and error handling (as required by the report)
  backendErrors: any;
}

const ProjectInputForm: React.FC<ProjectInputFormProps> = ({ projects, setProjects, backendErrors }) => {
  const [newProjectName, setNewProjectName] = useState('');
  const [newProjectCost, setNewProjectCost] = useState('');
  const [editId, setEditId] = useState<string | null>(null);

  // --- Core CRUD Logic ---

  const handleAddProject = () => {
    const cost = parseFloat(newProjectCost);

    // Strict input validation
    if (!newProjectName.trim() || isNaN(cost) || cost <= 0) {
      alert('Project name is required, and cost must be a positive number.');
      return;
    }

    const newProject: IProject = {
      id: Date.now().toString(), // Simple unique ID for frontend
      name: newProjectName.trim(),
      cost: cost,
    };

    setProjects([...projects, newProject]);
    setNewProjectName('');
    setNewProjectCost('');
  };

  const handleDeleteProject = (id: string) => {
    setProjects(projects.filter(p => p.id !== id));
  };

  const handleEditChange = (id: string, field: 'name' | 'cost', value: string) => {
    const updatedProjects = projects.map(p => {
      if (p.id === id) {
        if (field === 'cost') {
          const newCost = parseFloat(value) || 0;
          // Apply strict validation on the cost field
          if (newCost < 0) return p; 
          return { ...p, cost: newCost };
        }
        return { ...p, [field]: value };
      }
      return p;
    });
    setProjects(updatedProjects);
  };

  // --- Rendering Helpers ---
  
  const ProjectRow = React.memo(({ project }: { project: IProject }) => {
    const isEditing = editId === project.id;

    if (isEditing) {
      return (
        <div className="flex space-x-2 py-2 border-b bg-yellow-50 p-2 rounded-sm">
          <input 
            type="text" 
            value={project.name} 
            onChange={(e) => handleEditChange(project.id, 'name', e.target.value)}
            className="flex-grow p-1 border rounded text-sm"
          />
          <input 
            type="number" 
            value={project.cost.toFixed(0)} 
            onChange={(e) => handleEditChange(project.id, 'cost', e.target.value)}
            onBlur={() => setEditId(null)}
            className="w-20 p-1 border rounded text-sm text-right"
          />
          <button 
            onClick={() => handleDeleteProject(project.id)} 
            className="text-red-500 hover:text-red-700 text-sm"
          >
            🗑️
          </button>
        </div>
      );
    }

    return (
      <div 
        key={project.id} 
        onDoubleClick={() => setEditId(project.id)}
        className="flex justify-between items-center py-1 border-b text-sm transition hover:bg-gray-50 cursor-pointer"
      >
        <span className="truncate w-3/5">{project.name}</span>
        <span className="font-mono text-gray-800">${project.cost.toFixed(0)}</span>
        <button 
          onClick={() => handleDeleteProject(project.id)} 
          className="text-gray-400 hover:text-red-500 text-xs w-4 ml-2"
        >
          &times;
        </button>
      </div>
    );
  });
  
  // --- Main Component Render ---

  return (
    <div className="space-y-4 p-4 border rounded-lg bg-white shadow-sm">
      <h3 className="text-lg font-semibold border-b pb-2">Projects ({projects.length})</h3>

      {/* New Project Input Row */}
      <div className="flex space-x-2">
        <input
          type="text"
          value={newProjectName}
          onChange={(e) => setNewProjectName(e.target.value)}
          placeholder="Project Name"
          className="flex-grow p-2 border border-gray-300 rounded-md text-sm"
        />
        <input
          type="number"
          min="1"
          value={newProjectCost}
          onChange={(e) => setNewProjectCost(e.target.value)}
          placeholder="Cost ($)"
          className="w-20 p-2 border border-gray-300 rounded-md text-sm text-right"
        />
        <button
          onClick={handleAddProject}
          className="bg-green-500 text-white px-3 py-1 rounded-md hover:bg-green-600 transition text-sm"
          title="Add Project"
        >
          + Add
        </button>
      </div>

      {/* Project List: Scrollable Area */}
      {/* NOTE: For true scalability (N=1000), replace this div with react-window's FixedSizeList */}
      <div className="h-48 overflow-y-scroll border p-2 bg-gray-50 rounded-md">
        {projects.length === 0 ? (
          <p className="text-gray-500 italic text-center pt-8">Add projects to define your dataset.</p>
        ) : (
          projects.map(p => <ProjectRow key={p.id} project={p} />)
        )}
      </div>
      
      {/* Backend Errors (Pydantic validation) */}
      {backendErrors && (
        <p className="text-red-500 text-xs mt-2 border border-red-200 p-2 bg-red-50 rounded">
          Input validation failed: {JSON.stringify(backendErrors)}
        </p>
      )}
      
      <p className="text-xs text-gray-500 mt-2">Double-click a row to edit. The list supports up to 1000 projects for backend consumption, requiring a virtualized list for smooth scrolling.</p>
    </div>
  );
};

export default ProjectInputForm;