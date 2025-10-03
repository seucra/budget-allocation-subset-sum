// frontend/src/components/charts/MemoryUsageChart.tsx
import React from 'react';
import { Bar } from 'react-chartjs-2';
import { 
  Chart as ChartJS, 
  CategoryScale, 
  LinearScale, 
  BarElement, 
  Title, 
  Tooltip, 
  Legend 
} from 'chart.js';

ChartJS.register(
  CategoryScale, 
  LinearScale, 
  BarElement, 
  Title, 
  Tooltip, 
  Legend
);

// Note: Using the same data structure as the time chart for simplicity
interface BenchmarkDataPoint {
    input_size: number;
    brute_force_mem: number; // MB
    dp_mem: number; // MB
    greedy_mem: number; // MB
}

interface MemoryUsageChartProps {
  data: BenchmarkDataPoint[];
}

const MemoryUsageChart: React.FC<MemoryUsageChartProps> = ({ data }) => {
  // Use data for N=30 (or similar) to compare memory at a single complex point, 
  // as memory complexity is often analyzed at maximum load.
  const labels = data.map(d => d.input_size);
  const chartData = {
    labels: labels, 
    datasets: [
      {
        label: 'Dynamic Programming (MB)',
        data: data.map(d => d.dp_mem),
        backgroundColor: 'rgba(53, 162, 235, 0.7)',
      },
      {
        label: 'Greedy Heuristic (MB)',
        data: data.map(d => d.greedy_mem),
        backgroundColor: 'rgba(75, 192, 192, 0.7)',
      },
    ],
  };

  const options = {
    responsive: true,
    plugins: {
      legend: {
        position: 'top' as const,
      },
      title: {
        display: true,
        text: 'Algorithm Memory Usage vs. Input Size (N)',
      },
    },
    scales: {
        x: {
            title: {
                display: true,
                text: 'Input Size (Number of Projects)'
            }
        },
        y: {
            title: {
                display: true,
                text: 'Memory Used (MB)'
            }
        }
    }
  };

  return <Bar options={options} data={chartData} />;
};

export default MemoryUsageChart;