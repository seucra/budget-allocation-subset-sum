from fastapi.testclient import TestClient
from main import app

client = TestClient(app)

def test_health_endpoint():
    response = client.get("/health/")
    assert response.status_code == 200
    assert response.json() == {"status": "healthy", "database": "connected"}

def test_solve_dp():
    response = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "dp"})
    assert response.status_code == 200
    assert response.json()["total_cost"] == 30
    assert response.json()["indices"] == [2]

def test_solve_brute_force():
    response = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "brute_force"})
    assert response.status_code == 200
    assert response.json()["total_cost"] == 30
    assert response.json()["indices"] == [2]  # Known to fail, keeping as per your request

def test_solve_invalid_algorithm():
    response = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "invalid"})
    assert response.status_code == 400
    assert response.json()["detail"] == "Invalid algorithm"

def test_solve_negative_budget():
    response = client.post("/solve/", json={"costs": [10, 20, 30], "budget": -10, "algorithm": "dp"})
    assert response.status_code == 200
    assert response.json()["total_cost"] == 0
    assert response.json()["indices"] == []

def test_solve_empty_costs():
    response = client.post("/solve/", json={"costs": [], "budget": 30, "algorithm": "dp"})
    assert response.status_code == 200
    assert response.json()["total_cost"] == 0
    assert response.json()["indices"] == []

def test_compare():
    response = client.post("/compare/", json={"costs": [10, 20, 30], "budget": 30})
    assert response.status_code == 200
    assert len(response.json()) == 5
    for result in response.json():
        assert result["total_cost"] <= 30
        assert all(i >= 0 and i < len([10, 20, 30]) for i in result["indices"])

def test_no_duplicate_run_ids():
    response1 = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "dp"})
    run_id1 = response1.json()["run_id"]
    response2 = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "dp"})
    run_id2 = response2.json()["run_id"]
    assert run_id1 != run_id2

def test_results_endpoint():
    # Run a solve to create a record
    solve_response = client.post("/solve/", json={"costs": [10, 20, 30], "budget": 30, "algorithm": "dp"})
    run_id = solve_response.json()["run_id"]
    response = client.get(f"/results/{run_id}")
    assert response.status_code == 200
    assert response.json()["run_id"] == run_id
    assert response.json()["total_cost"] == 30
    assert response.json()["indices"] == [2]
