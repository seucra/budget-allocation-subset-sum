// frontend/src/main.tsx

import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App.tsx';
import './style.css';

// IMPORTANT: This file imports your global CSS file, which should contain the Tailwind directives.
import './style.css'; 

// Use the non-null assertion operator (!) since 'root' exists in frontend/index.html
ReactDOM.createRoot(document.getElementById('app')!).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
);