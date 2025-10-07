// frontend/src/components/Layout.tsx
import React from 'react';
import { Link } from 'react-router-dom';

interface LayoutProps {
  children: React.ReactNode;
}

const navItems = [
  { name: 'Home', path: '/' },
  { name: 'Solver', path: '/solve' },
  { name: 'History', path: '/history' },
  { name: 'Analytics', path: '/analytics' },
];

const Layout: React.FC<LayoutProps> = ({ children }) => {
  return (
    <div className="min-h-screen bg-gray-100">
      {/* Navigation Bar */}
      <header className="bg-white shadow-md">
        <nav className="container mx-auto px-6 py-3 flex justify-between items-center">
          <Link to="/" className="text-2xl font-bold text-indigo-600">
            Budget Solver
          </Link>
          <div className="flex space-x-6">
            {navItems.map((item) => (
              <Link
                key={item.name}
                to={item.path}
                className="text-gray-600 hover:text-indigo-600 transition duration-150 font-medium"
              >
                {item.name}
              </Link>
            ))}
          </div>
        </nav>
      </header>

      {/* Main Content Area */}
      <main className="pb-10">
        {children}
      </main>

      {/* Optional Footer */}
      <footer className="bg-gray-800 text-white text-center p-4 text-sm">
        Budget Allocation Subset Sum Project | Backend: FastAPI + C++ Engine
      </footer>
    </div>
  );
};

export default Layout;