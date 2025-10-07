// frontend/src/App.tsx

import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Layout from './components/Layout';
import HomePage from './pages/HomePage';
import SolverPage from './pages/SolverPage';
import HistoryPage from './pages/HistoryPage';
import AnalyticsPage from './pages/AnalyticsPage';

function App() {
  return (
    // 1. BrowserRouter wraps the entire application
    <Router>
      {/* 2. Layout provides the persistent navigation bar and basic styling structure */}
      <Layout>
        <Routes>
          {/* Main Pages */}
          <Route path="/" element={<HomePage />} />
          <Route path="/solve" element={<SolverPage />} />
          <Route path="/history" element={<HistoryPage />} />
          <Route path="/analytics" element={<AnalyticsPage />} />
          
          {/* Fallback 404 Route */}
          <Route path="*" element={<div className="container mx-auto p-8 text-center text-red-600">404 - Page Not Found</div>} />
        </Routes>
      </Layout>
    </Router>
  );
}

export default App;