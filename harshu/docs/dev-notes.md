---

## 🧩 Core Problem

Implement a system to solve variations of the **Subset Sum Problem (SSP)** for **budget allocation**:

* Given a list of projects (each with a cost), select a subset whose total cost best fits within a defined budget.

---

## ✅ Functional Requirements (Features)

### 1. **Project Management**

* Add/remove/edit projects with cost values.
* Assign optional metadata: department, priority, risk factor, time phase, etc.

### 2. **Budget Control**

* Set a total available budget (single value).
* Optionally support:

  * Time-phased budgets (e.g., monthly/yearly).
  * Multi-department budgets.

### 3. **Algorithm Engine**

* **Algorithms to Implement**:

  * Brute Force (baseline)
  * Dynamic Programming (exact match)
  * Backtracking (recursive exploration)
  * Greedy Heuristic (approximate)
  * Hybrid strategies (combine approaches)
* Support **comparison mode**: run multiple algorithms side-by-side.

### 4. **Smart Solver (Optional)**

* Auto-select algorithm based on:

  * Input size
  * Budget-to-total-cost ratio
  * Project cost distribution
* Use ML models to predict optimal algorithm if available.

### 5. **Result Dashboard**

* Display:

  * Selected project subset
  * Total cost vs. budget
  * Unused budget (if any)
  * Execution time and memory usage per algorithm
  * Accuracy indicators (exact match, close match, heuristic score)

### 6. **Visualization**

* Execution steps (esp. for DP and backtracking)
* Subset tree/graph traversal
* Input and output distribution graphs

### 7. **Analytics Panel**

* Performance metrics:

  * Time and space complexity
  * Accuracy/success rate
* Dataset scaling behavior (small/medium/large inputs)
* Memory usage charts

### 8. **Export & API Access**

* Export results as:

  * CSV / JSON / PDF
  * Visuals as PNG/SVG
* REST API access for:

  * Submitting project sets
  * Querying results
  * Integrating solver into other systems

### 9. **User Experience Enhancements**

* Real-time feedback as user inputs change.
* Highlight why a project was selected (or not).
* Educational tooltips (e.g., explain how DP works in this context).

---

## 🔍 Niche/Advanced Requirements

### 🔧 Advanced Problem Support

* **Multi-budget allocation**: Optimize allocation across several budget pools.
* **Priority-weighted selection**: Factor in project importance during subset selection.
* **Risk-adjusted budgeting**: Include project risk as a filter or scoring component.
* **Time-phased selection**: Handle temporal constraints (e.g., allocate across fiscal quarters).

### 🤖 Machine Learning-Driven Optimization

* Extract features:

  * n (project count), budget ratio, cost variance, mean/max cost
* Use trained model to:

  * Predict best-fitting algorithm for input
  * Recommend project combinations based on learned patterns

### ⚙️ Performance Optimization

* Caching:

  * Store & reuse results for identical inputs
* Lazy computation:

  * Defer heavy computations until necessary
* Profiling support (via `cProfile`, `memory_profiler`, `timeit`)

---

## 🧱 Non-Functional Requirements (Developer Focus)

### System Architecture

```
[Frontend UI] ←→ [Algorithm Engine] ←→ [Data Store] ←→ [Analytics Layer]
```

### Tech Stack

* **Languages**: Python (core),
* **Frontend**: Streamlit (rapid) or React (scalable)
* **Backend**: FastAPI
* **Database**: SQLite (dev), PostgreSQL (prod)
* **Visualization**: Matplotlib
* **Testing**: `pytest`, `Jest`
* **Deployment**: Dockerized, CI/CD optional

---

## 🧪 Developer-Specific Considerations

* **Edge Case Coverage**:

  * Empty input
  * Zero budget
  * All projects > budget
  * Duplicate costs

* **Extensibility**:

  * New algorithms can be plugged in via modular interfaces.
  * Algorithm benchmarking is abstracted and reusable.

* **Interface Contracts**:

  * Algorithms must accept a consistent input schema:

    ```python
    def solve(projects: List[Dict], budget: int) -> List[int]
    ```
  * Must return:

    ```python
    {
      "selected_indices": [...],
      "total_cost": int,
      "execution_time": float,
      "memory_used": float
    }
    ```

* **Test Coverage Targets**:

  * Algorithm correctness (unit tests)
  * Performance thresholds (integration tests)
  * UI stability (e2e tests if React)

---


