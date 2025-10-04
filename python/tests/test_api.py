from fastapi.testclient import TestClient
from api.main import app

client = TestClient(app)

def test_solve_endpoint_brute_force():
    payload = {
        "projects": [{"name": "P1", "cost": 100}, {"name": "P2", "cost": 200}],
        "budget": 300,
        "algorithm": "brute_force"
    }
    response = client.post("/solve", json=payload)
    assert response.status_code == 200
    assert response.json()["selected_indices"] == [0, 1]
    assert response.json()["total_cost"] == 300

def test_solve_endpoint_greedy():
    payload = {
        "projects": [{"name": "P1", "cost": 100}, {"name": "P2", "cost": 200}],
        "budget": 300,
        "algorithm": "greedy"
    }
    response = client.post("/solve", json=payload)
    assert response.status_code == 200
    assert response.json()["selected_indices"] == [0, 1]
    assert response.json()["total_cost"] == 300
