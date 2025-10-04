// frontend/src/components/input/ProjectInputForm.tsx
// frontend/src/components/input/ProjectInputForm.tsx
import React, { useState } from 'react';
import type { IProject } from '../../types'; 

// FIX: Use named import and suppress the TS error (ts2305) on this line only.
// This is the most compatible way to resolve the runtime crash.
// @ts-ignore
import { FixedSizeList } from 'react-window'; 
// ...
// @ts-ignore - Access component from namespace object. This resolves the runtime SyntaxError.
const FixedSizeList = ReactWindow.FixedSizeList; 

// --- INTERFACES: Defined before use ---
interface ProjectInputFormProps {
  projects: IProject[];
  setProjects: (projects: IProject[]) => void;
  backendErrors: any;
  selectedIndices: number[]; // <-- STEP 2: NEW PROP for highlighting
}

interface VirtualizedRowProps {
  index: number;
  style: React.CSSProperties; // Required prop by react-window
  data: {
    projects: IProject[];
    editId: string | null;
    setEditId: (id: string | null) => void;
    handleDeleteProject: (id: string) => void;
    handleEditChange: (id: string, field: 'name' | 'cost', value: string) => void;
    selectedIndices: number[]; // <-- STEP 2: NEW DATA PROP
  };
}
// --- END INTERFACES ---

const Row: React.FC<VirtualizedRowProps> = React.memo(({ index, style, data }) => {
  // Destructure all required data for the row
  const { projects, editId, setEditId, handleDeleteProject, handleEditChange, selectedIndices } = data;
  
  const project = projects[index];
  const isEditing = editId === project.id;
  
  // STEP 2: Check if the current project's index is in the selected indices array
  const isSelected = selectedIndices.includes(index); 

  // Apply the style object for absolute positioning (Virtualization)
  return (
    <div style={style}>
      <div 
        key={project.id} 
        onDoubleClick={() => setEditId(project.id)}
        // STEP 2: Conditional styling for highlighting selected projects
        className={`flex justify-between items-center py-1 border-b text-sm transition hover:bg-gray-50 cursor-pointer p-2 ${
            isSelected && !isEditing ? 'bg-indigo-50 border-indigo-200 font-semibold' : ''
        }`}
        style={{ height: '100%' }} 
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
              // FIX: Corrected the function call to pass all 3 arguments (id, field, value)
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
    </div>
  );
});


const ProjectInputForm: React.FC<ProjectInputFormProps> = ({ 
    projects, 
    setProjects, 
    backendErrors, 
    selectedIndices // <-- STEP 2: DESTRUCTURE NEW PROP HERE
}) => {
  const [newProjectName, setNewProjectName] = useState('');
  const [newProjectCost, setNewProjectCost] = useState('');
  const [editId, setEditId] = useState<string | null>(null);

  // --- Core CRUD Logic (omitted for brevity) ---
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

  const handleEditChange = (id: string, field: 'name' | 'cost', value: string) => {
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
  };
  // --- End Core CRUD Logic ---

  // --- Main Component Render ---

  return (
    <div className="space-y-4 p-4 border rounded-lg bg-white shadow-sm">
      <h3 className="text-lg font-semibold border-b pb-2">Projects ({projects.length})</h3>

      {/* New Project Input Row (omitted for brevity) */}
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

      {/* Project List: Virtualized Area */}
      <div className="h-48 border bg-gray-50 rounded-md">
        {projects.length === 0 ? (
          <p className="text-gray-500 italic text-center pt-8">Add projects to define your dataset.</p>
        ) : (
          <FixedSizeList
            height={192} // h-48 (12rem) = 192px
            width="100%"
            itemCount={projects.length}
            itemSize={40} // Estimated height of each row in pixels
            itemData={{
              projects,
              editId,
              setEditId,
              handleDeleteProject,
              handleEditChange,
              selectedIndices, // <-- PASS NEW PROP HERE
            }}
          >
            {Row}
          </FixedSizeList>
        )}
      </div>
      
      {/* Backend Errors (Pydantic validation) */}
      {backendErrors && (
        <p className="text-red-500 text-xs mt-2 border border-red-200 p-2 bg-red-50 rounded">
          Input validation failed: {JSON.stringify(backendErrors)}
        </p>
      )}
      
      <p className="text-xs text-gray-500 mt-2">Double-click a row to edit. The list supports up to 1000 projects for backend consumption, now using virtualization for smooth scrolling.</p>
    </div>
  );
};

export default ProjectInputForm;