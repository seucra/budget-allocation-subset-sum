import plotly.graph_objects as go
import requests

response = requests.post("http://127.0.0.1:8000/compare/", json={"costs": [10, 20, 30], "budget": 30})
results = response.json()

algorithms = [r["algorithm"] for r in results]
times = [r["execution_time_ms"] for r in results]
memory = [r["memory_used_mb"] for r in results]
accuracy = [r["accuracy"] for r in results]

fig = go.Figure(data=[
    go.Bar(name="Execution Time (ms)", x=algorithms, y=times),
    go.Bar(name="Memory Used (MB)", x=algorithms, y=memory, yaxis="y2"),
    go.Bar(name="Accuracy", x=algorithms, y=accuracy, yaxis="y3")
])
fig.update_layout(
    title="Algorithm Performance Comparison",
    yaxis=dict(title="Time (ms)"),
    yaxis2=dict(title="Memory (MB)", overlaying="y", side="right"),
    yaxis3=dict(title="Accuracy", overlaying="y", side="right", position=0.85)
)
fig.show()
