// src/DBLayer/DatabaseManager.cpp
#include "DatabaseManager.h"
#include "DataModel/DataSet.h"
#include "DataModel/SolverResult.h"

#include <pqxx/pqxx>
#include <iostream>
#include <sstream>

// This header is needed for pqxx::zview
#include <pqxx/zview.hxx>

std::string DatabaseManager::to_sql_array(const std::vector<int>& vec) {
    if (vec.empty()) return "{}";
    std::stringstream ss;
    ss << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i] << (i == vec.size() - 1 ? "" : ",");
    }
    ss << "}";
    return ss.str();
}

DatabaseManager::DatabaseManager(const std::string& conn_string)
    : m_conn_string(conn_string), m_connection(nullptr) {}

// BUG FIX: Defining the destructor in the .cpp file where pqxx::connection
// is a complete type allows the std::unique_ptr to be destroyed correctly.
DatabaseManager::~DatabaseManager() {}

void DatabaseManager::connect() {
    try {
        m_connection = std::make_unique<pqxx::connection>(m_conn_string);
    } catch (const std::exception &e) {
        std::cerr << "Database connection failed: " << e.what() << std::endl;
        throw;
    }
}

long DatabaseManager::saveResult(const DataSet& data, const SolverResult& result, const std::string& algorithm) {
    if (!m_connection || !m_connection->is_open()) {
        throw std::runtime_error("Not connected to the database.");
    }
    try {
        pqxx::work txn(*m_connection);
        long dataset_id;
        std::string numbers_sql = to_sql_array(data.numbers);

        // WARNING FIX: Using txn.exec_params() as it seems the newer API is not available or has different overloads
        pqxx::result res = txn.exec_params("SELECT dataset_id FROM datasets WHERE numbers = $1 AND target_sum = $2", numbers_sql, data.target_sum);
        
        if (res.empty()) {
            dataset_id = txn.exec_params1("INSERT INTO datasets (numbers, target_sum) VALUES ($1, $2) RETURNING dataset_id", numbers_sql, data.target_sum)[0].as<long>();
        } else {
            dataset_id = res[0][0].as<long>();
        }

        long result_id = txn.exec_params1("INSERT INTO solve_results (dataset_id, algorithm_used, execution_time_ms, solution_found) VALUES ($1, $2, $3, $4) RETURNING result_id", dataset_id, algorithm, result.execution_time.count(), result.solution_exists)[0].as<long>();
        
        if (result.solution_exists) {
            for (const auto& subset : result.subsets) {
                txn.exec_params("INSERT INTO result_subsets (result_id, subset_data) VALUES ($1, $2)", result_id, to_sql_array(subset));
            }
        }
        
        txn.commit();
        std::cout << "Successfully saved result to database with ID: " << result_id << std::endl;
        return result_id;
    } catch (const std::exception &e) {
        std::cerr << "Database transaction failed: " << e.what() << std::endl;
        throw;
    }
}
