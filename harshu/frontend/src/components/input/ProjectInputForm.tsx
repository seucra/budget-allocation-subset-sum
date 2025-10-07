// frontend/src/components/input/ProjectInputForm.tsx
import React, { useState, useCallback } from 'react';
import type { IProject } from '../../types'; 

// Debounce Utility Function
const debounce = (func: (...args: any[]) => void, delay: number) => {
    let timeoutId: any = null; 
    
    return (...args: any[]) => {
        if (timeoutId) {
            clearTimeout(timeoutId);
        }
        timeoutId = setTimeout(() => {
            func.apply(null, args);
        }, delay);
    };
};

// --- INTERFACES ---
interface ProjectInputFormProps {
  projects: IProject[];
  setProjects: (projects: IProject[]) => void;
  backendErrors: any;
  selectedIndices: number[]; 
}

interface VirtualizedRowProps {
  index: number;
  style: React.CSSProperties;
  data: {
    projects: IProject[];
    editId: string | null;
    setEditId: (id: string | null) => void;
    handleDeleteProject: (id: string) => void;
    handleEditChange: (id: string, field: 'name' | 'cost', value: string) => void;
    selectedIndices: number[];
  };
}
// --- END INTERFACES ---

// Simple fallback component without react-window
const SimpleProjectList: React.FC<{
  projects: IProject[];
  editId: string | null;
  setEditId: (id: string | null) => void;
  handleDeleteProject: (id: string) => void;
  handleEditChange: (id: string, field: 'name' | 'cost', value: string) => void;
  selectedIndices: number[];
}> = ({ projects, editId, setEditId, handleDeleteProject, handleEditChange, selectedIndices }) => {
  return (
    <div style={{ height: '192px', overflow: 'auto' }}>
      {projects.map((project, index) => {
        const isEditing = editId === project.id;
        const isSelected = selectedIndices.includes(index);
        
        return (
          <div 
            key={project.id} 
            onDoubleClick={() => setEditId(project.id)}
            className={`flex justify-between items-center py-2 px-3 border-b text-sm transition hover:bg-gray-50 cursor-pointer ${
              isSelected && !isEditing ? 'bg-indigo-50 border-indigo-200 font-semibold' : ''
            }`}
            style={{ height: '40px' }}
          >
            {isEditing ? (
              <div className="flex space-x-2 w-full bg-yellow-50 p-1 rounded-sm">
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
            ) : (
              <>
                <span className="truncate w-3/5">{project.name}</span>
                <span className="font-mono text-gray-800">${project.cost.toFixed(0)}</span>
                <button 
                  onClick={() => handleDeleteProject(project.id)} 
                  className="text-gray-400 hover:text-red-500 text-xs w-4 ml-2"
                >
                  &times;
                </button>
              </>
            )}
          </div>
        );
      })}
    </div>
  );
};

const ProjectInputForm: React.FC<ProjectInputFormProps> = ({ 
    projects, 
    setProjects, 
    backendErrors, 
    selectedIndices 
}) => {
  const [newProjectName, setNewProjectName] = useState('');
  const [newProjectCost, setNewProjectCost] = useState('');
  const [editId, setEditId] = useState<string | null>(null);

  // Implement debounced handler
  const handleEditChange = useCallback(
    debounce(
      (id: string, field: 'name' | 'cost', value: string) => {
        const updatedProjects = projects.map(p => {
          if (p.id === id) {
            if (field === 'cost') {
              const newCost = parseFloat(value) || 0;
              if (newCost < 0) return p; 
              return { ...p, cost: newCost };
            }
            return { ...p, [field]: value };
          }
          return p;
        });
        setProjects(updatedProjects);
      },
      300 
    ),
    [projects, setProjects] 
  );

  const handleAddProject = () => {
    const cost = parseFloat(newProjectCost);
    if (!newProjectName.trim() || isNaN(cost) || cost <= 0) {
      alert('Project name is required, and cost must be a positive number.');
      return;
    }

    const newProject: IProject = {
      id: Date.now().toString(),
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

      {/* Project List: Using Simple List Instead of Virtualized */}
      <div className="h-48 border bg-gray-50 rounded-md">
        {projects.length === 0 ? (
          <p className="text-gray-500 italic text-center pt-8">Add projects to define your dataset.</p>
        ) : (
          <SimpleProjectList
            projects={projects}
            editId={editId}
            setEditId={setEditId}
            handleDeleteProject={handleDeleteProject}
            handleEditChange={handleEditChange}
            selectedIndices={selectedIndices}
          />
        )}
      </div>
      
      {/* Backend Errors */}
      {backendErrors && (
        <p className="text-red-500 text-xs mt-2 border border-red-200 p-2 bg-red-50 rounded">
          Input validation failed: {JSON.stringify(backendErrors)}
        </p>
      )}
      
      <p className="text-xs text-gray-500 mt-2">Double-click a row to edit. The list supports up to 1000 projects.</p>
    </div>
  );
};

export default ProjectInputForm;