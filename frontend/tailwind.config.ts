import type { Config } from "tailwindcss";
import animate from "tailwindcss-animate";

const config: Config = {
  darkMode: 'class',
  content: ['./src/**/*.{js,ts,jsx,tsx}', './index.html'],
  
  // Remove the entire 'theme' section and replace with:
  theme: {
    extend: {
      // Your custom colors and styles here if needed
    },
  },
  
  plugins: [animate],
};

export default config;