// frontend/src/components/charts/ExecutionTimeChart.tsx
import React from 'react';
import { Line } from 'react-chartjs-2';
import { 
  Chart as ChartJS, 
  CategoryScale, 
  LinearScale, 
  PointElement, 
  LineElement, 
  Title, 
  Tooltip, 
  Legend 
} from 'chart.js';

// Register Chart.js components
ChartJS.register(
  CategoryScale, 
  LinearScale, 
  PointElement, 
  LineElement, 
  Title, 
  Tooltip, 
  Legend
);

interface BenchmarkDataPoint {
  input_size: number;
  brute_force_time: number;
  dp_time: number;
  greedy_time: number;
}

interface ExecutionTimeChartProps {
  data: BenchmarkDataPoint[];
}

const ExecutionTimeChart: React.FC<ExecutionTimeChartProps> = ({ data }) => {
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
        label: 'Brute Force (ms)',
        data: data.map(d => d.brute_force_time),
        borderColor: 'rgb(255, 99, 132)',
        backgroundColor: 'rgba(255, 99, 132, 0.5)',
        tension: 0.1,
      },
      {
        label: 'Dynamic Programming (ms)',
        data: data.map(d => d.dp_time),
        borderColor: 'rgb(53, 162, 235)',
        backgroundColor: 'rgba(53, 162, 235, 0.5)',
        tension: 0.1,
      },
      {
        label: 'Greedy Heuristic (ms)',
        data: data.map(d => d.greedy_time),
        borderColor: 'rgb(75, 192, 192)',
        backgroundColor: 'rgba(75, 192, 192, 0.5)',
        tension: 0.1,
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
        text: 'Algorithm Execution Time vs. Input Size (N)',
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
          text: 'Time (ms)'
        },
        type: 'linear' as const // Changed from logarithmic to linear for now
      }
    }
  };

  return <Line options={options} data={chartData} />;
};

export default ExecutionTimeChart;