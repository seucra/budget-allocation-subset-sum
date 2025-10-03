> Here’s a **detailed, frontend-focused report** crafted specifically with the backend architecture and details in mind. The focus is on how frontend development should align with backend capabilities and constraints to build a robust, performant, and user-friendly app.

---

# Frontend Development Report: Budget Allocation Using Subset Sum

**Considering Python FastAPI + C++ Algorithm Engine + PostgreSQL Backend**

---

## 1. Frontend Features Aligned with Backend Capabilities

### 1.1 Dynamic Project & Budget Management

* **Frontend must support:**

  * Creating, editing, and deleting project entries (name, cost).
  * Defining budgets dynamically per project set.
  * Integration with backend `POST /datasets/` and `GET /datasets/{id}/` endpoints to store and retrieve datasets (ProjectSet + Budget).
* **Backend impact:**

  * Efficient form validation on frontend to minimize invalid API calls.
  * Support batch upload or edits to reduce network overhead.
  * Use Pydantic validation errors from backend to inform users precisely.

### 1.2 Algorithm Selection & Execution Control

* **Frontend must support:**

  * Algorithm dropdown or toggle, supporting backend algorithms: Brute Force, DP, Backtracking, Greedy, Hybrid.
  * Option to omit algorithm (let backend auto-select via ML or heuristic).
  * Invoke `POST /solve/` with selected algorithm and dataset, handling async responses and errors.
* **Backend impact:**

  * Frontend shows execution status, runtime, memory usage, and status (`exact`, `approximate`, `failed`) from backend.
  * Provide loading spinners or progress bars for longer runs.
  * Display detailed backend execution metrics returned in JSON for transparency.

### 1.3 Results Visualization & Comparison

* **Frontend must support:**

  * Display selected project indices and total cost per algorithm run.
  * Show side-by-side comparisons of multiple runs or algorithms for the same dataset.
  * Render algorithm execution statistics (time, memory, accuracy).
  * Graphical visualization of subsets selected (highlight projects in list).
  * Support fetching historic runs from backend `GET /results/{run_id}/`.
* **Backend impact:**

  * Use structured data from `AlgorithmRun` DB table to populate history dashboards.
  * Visualize analytics data (benchmarking from `AnalyticsSnapshot`) if available.

---

## 2. Frontend-Backend Interaction & Data Handling

### 2.1 API Integration

* Use typed REST API clients (e.g., TypeScript interfaces) matching backend Pydantic models to ensure request/response consistency.
* Implement robust error handling for:

  * Validation errors (display field-specific messages).
  * Execution failures or timeouts (show backend `status` messages).
* Implement caching or local storage for project sets to reduce repeat API calls.

### 2.2 Data Structures & State Management

* Mirror backend data entities:

  * ProjectSet, Project, Budget, AlgorithmRun.
* Use centralized state management (React Context, Redux) for:

  * Current project list and budget.
  * Current and historical algorithm runs.
* Normalize data to efficiently update project lists and results without redundant re-renders.

---

## 3. UI/UX Design Considerations

### 3.1 Responsiveness & Performance

* Backend can handle up to 1000 projects; frontend must:

  * Use virtualized lists (e.g., `react-window`) for large project sets to avoid DOM bloat.
  * Debounce inputs before sending to backend to minimize API traffic.
  * Lazy-load historic runs and benchmarking data on demand.

### 3.2 User Feedback & Transparency

* Real-time display of algorithm execution time and memory usage from backend profiling.
* Show precise status updates (`exact`, `approximate`, `failed`) clearly.
* Display explanations/tooltips describing each algorithm's pros/cons (from backend docs or inline content).

### 3.3 Accessibility & Error Prevention

* Strict input validation matching backend constraints (positive costs, reasonable budget).
* Graceful handling of edge cases: empty projects, zero budgets, unmatchable budgets.
* Accessibility compliance (ARIA labels, keyboard navigation).

---

## 4. Visualizations & Analytics Dashboard

### 4.1 Execution & Benchmark Visualization

* Use frontend libraries like Chart.js or D3 to plot:

  * Execution time vs input size.
  * Memory usage charts.
  * Accuracy (exact vs approximate rates).
* Fetch analytics snapshots from backend to populate dashboard views.

### 4.2 Step-by-Step Algorithm Execution (Optional)

* Visualize algorithm steps if backend exposes execution traces (e.g., DP state table).
* Use animations or state transitions to educate users about the solving process.

---

## 5. Frontend Challenges Considering Backend Constraints

### 5.1 Handling Asynchronous Calls & Latency

* Backend runs complex C++ algorithms with possible multi-second runtimes; frontend must:

  * Provide non-blocking UI with loading states.
  * Possibly poll `GET /results/{run_id}/` if solve endpoint is async.
  * Manage timeouts and retries gracefully.

### 5.2 Synchronization Between Frontend & Backend Data

* Keep local UI state consistent with backend database state (e.g., after dataset creation or algorithm runs).
* Handle concurrent modifications or multiple users (if multi-user support added).

### 5.3 Complex Data Modeling

* Backend JSONB metadata fields may contain complex nested info; frontend must parse and display these cleanly.
* Avoid tight coupling to backend internal representations to allow future schema changes.

---

## 6. Recommended Frontend Technology & Architecture

| Aspect           | Recommendation                                     |
| ---------------- | -------------------------------------------------- |
| Framework        | React + TypeScript for type safety and scalability |
| State Management | Redux Toolkit or React Context + hooks             |
| API Client       | Axios or Fetch with generated TypeScript typings   |
| Styling          | Tailwind CSS or Material-UI for rapid styling      |
| Visualization    | Chart.js, Recharts, or D3 for charts and graphs    |
| Form Handling    | React Hook Form for validation with custom rules   |
| Performance      | React Window for large lists, memoization          |
| Testing          | Jest + React Testing Library                       |
| Deployment       | Vercel / Netlify for frontend hosting              |

---

## 7. Summary & Alignment with Backend

| Frontend Aspect           | Backend Dependency/Consideration                              |
| ------------------------- | ------------------------------------------------------------- |
| Dataset & Budget Input    | Sync with `POST /datasets/`, use Pydantic validation feedback |
| Algorithm Selection & Run | Align with `POST /solve/`, consume execution stats, status    |
| Result Display & History  | Leverage `GET /results/{run_id}/` and DB stored runs          |
| Performance Visualization | Use backend profiling and benchmarking data                   |
| Error Handling            | Surface backend validation and execution errors clearly       |
| Scalability               | Use virtualization due to large project sets                  |
| Async UX                  | Handle possible latency due to complex C++ algorithm runs     |

---

