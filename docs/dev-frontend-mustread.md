# Frontend Perspective Report: Budget Allocation using Subset Sum

---

### Key Features to Develop (Phase 3 focus + overall frontend scope)

1. **Interactive Project Management Panel**

   * Add/remove/edit projects with associated costs
   * Dynamic form inputs for project data entry
   * Validation for input correctness (e.g., cost as positive numbers)

2. **Budget Control Interface**

   * Input and adjust total budget dynamically
   * Range sliders or input fields with live validation

3. **Algorithm Selector UI**

   * Dropdown or toggle buttons to choose algorithms (Brute Force, DP, Backtracking, Greedy)
   * Ability to run multiple algorithms side-by-side for comparison

4. **Results Dashboard**

   * Display algorithm outputs side-by-side
   * Highlight matched subsets/projects
   * Show metrics like execution time and memory usage per algorithm

5. **Visualization Area**

   * Graphical representation of algorithm execution steps (e.g., state transitions in DP)
   * Progress bars or spinners for ongoing computations
   * Chart components for performance (bar charts, line graphs)

6. **Educational Elements**

   * Tooltips or expandable sections explaining each algorithm’s approach
   * Inline comments or step-by-step walkthroughs
   * User guidance or help sections

---

### Points of Focus & Considerations

* **Responsiveness & Interactivity**
  Ensure smooth user experience with real-time updates on inputs and results without page reloads.
  Use React state management or Streamlit reactive features effectively.

* **Performance & Scalability**
  Frontend should handle up to 1000 projects without UI lag. Lazy rendering and virtualization might be needed for large lists.

* **Data Validation & Error Handling**
  Validate user inputs (budget and project costs) immediately to prevent invalid computations.
  Show user-friendly error messages and handle edge cases like empty inputs or zero budgets gracefully.

* **Modular & Maintainable UI Architecture**
  Design reusable React components (e.g., ProjectItem, AlgorithmSelector, ResultCard).
  Separate logic from presentation for easier testing and scaling.

* **Visual Feedback & Loading States**
  Use progress indicators during long-running computations or data fetches.
  Animate state changes or algorithm steps for better engagement.

* **Accessibility & Usability**
  Keyboard navigation support, ARIA labels for screen readers.
  Clear, intuitive layout with consistent styling and visual hierarchy.

* **Cross-browser Compatibility**
  Ensure UI behaves consistently across major browsers and devices.

---

### Potential Complications & Challenges

* **Handling Large Data Sets**
  Rendering and managing UI for hundreds to thousands of projects could cause performance issues (slow rendering, high memory).
  Solutions: Virtual scrolling, pagination, memoization.

* **Real-time Algorithm Comparison**
  Running multiple algorithm calculations and updating UI simultaneously may impact responsiveness.
  Use Web Workers or debounce input changes to reduce UI freezes.

* **Dynamic Visualization Complexity**
  Showing step-by-step algorithm states graphically can be complex, especially for DP/backtracking methods.
  Requires efficient state management and possibly custom drawing (SVG/Canvas).

* **User Input Complexity**
  Allowing flexible project input (bulk upload, editing) while maintaining data integrity may complicate the UI logic.

* **Cross-Technology Integration**
  If backend algorithms run asynchronously (FastAPI/Node.js), frontend must handle API calls, loading states, error handling robustly.

* **Styling Consistency**
  Choosing and sticking to a CSS framework (Material-UI/Tailwind) and ensuring responsive design across components.

---

### Recommended Frontend Tech Stack & Tools

* **Framework**: React + TypeScript (scalable, strong typing)
* **State Management**: React Context / Redux for complex state
* **Styling**: Tailwind CSS or Material-UI for fast, consistent UI
* **Visualization**: Chart.js, D3.js or React-vis for charts and graphs
* **Testing**: Jest + React Testing Library for unit and integration tests
* **Prototyping**: Figma for wireframes, Miro for flow diagrams
* **Performance Debugging**: React DevTools, Chrome DevTools
* **Deployment**: Vercel or Heroku for hosting frontend apps

---

### Summary

The frontend is the primary user interaction layer and needs to:

* Provide intuitive, dynamic controls for project & budget input
* Support multiple algorithm selection and clear side-by-side result display
* Visualize algorithm processes and performance metrics interactively
* Handle large datasets efficiently with performant rendering
* Be accessible, responsive, and visually engaging
* Integrate cleanly with backend services for algorithm execution and data persistence

Challenges mostly stem from data size, real-time updates, and complex visualization needs. Using a modular React architecture with a strong UI framework and clear state management will mitigate many risks.

---

