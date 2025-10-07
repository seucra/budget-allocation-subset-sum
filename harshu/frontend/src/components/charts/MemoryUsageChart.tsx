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

interface BenchmarkDataPoint {
  input_size: number;
  brute_force_mem: number;
  dp_mem: number;
  greedy_mem: number;
}

interface MemoryUsageChartProps {
  data: BenchmarkDataPoint[];
}

const MemoryUsageChart: React.FC<MemoryUsageChartProps> = ({ data }) => {
  // Add safety check for empty data
  if (!data || data.length === 0) {
    return (
      <div className="flex items-center justify-center h-full">
        <p className="text-gray-500">No data available for chart</p>
      </div>
    );
  }

  const chartData = {
    labels: data.map(d => d.input_size),
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
    maintainAspectRatio: false, // Important for fixed container height
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