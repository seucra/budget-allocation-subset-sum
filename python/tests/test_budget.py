import pytest
import budget_module

def test_brute_force():
    result = budget_module.brute_force_subset_sum([100, 200], 300)
    assert result.indices == [0, 1]
    assert result.total_cost == 300
    assert result.execution_time >= 0

def test_greedy():
    result = budget_module.greedy_subset_sum([100, 200], 300)
    assert result.indices == [0, 1]
    assert result.total_cost == 300
    assert result.execution_time >= 0

def test_empty():
    result = budget_module.greedy_subset_sum([], 100)
    assert result.indices == []
    assert result.total_cost == 0
