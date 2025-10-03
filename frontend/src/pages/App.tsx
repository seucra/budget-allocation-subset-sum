// frontend/src/App.tsx

import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import HomePage from './pages/HomePage';
import SolverPage from './pages/SolverPage';
import HistoryPage from './pages/HistoryPage';
import AnalyticsPage from './pages/AnalyticsPage';
import Layout from './components/Layout'; // You'll create this for navigation/header

function App() {
  return (
    <Router>
      {/* Layout component wraps all pages for persistent elements like the navigation bar */}
      <Layout>
        <Routes>
          <Route path="/" element={<HomePage />} />
          <Route path="/solve" element={<SolverPage />} />
          <Route path="/history" element={<HistoryPage />} />
          <Route path="/analytics" element={<AnalyticsPage />} />
          {/* Add a fallback route for 404s */}
          <Route path="*" element={<div>404 - Not Found</div>} /> 
        </Routes>
      </Layout>
    </Router>
  );
}

export default App;