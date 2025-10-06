// src/DBLayer/DatabaseManager.h
#pragma once

#include <string>
#include <memory>
#include <vector>

// Forward-declare pqxx connection
namespace pqxx {
    class connection;
}

// Forward-declare our data structures
struct DataSet;
struct SolverResult;

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& conn_string);
    ~DatabaseManager(); // DESTRUCTOR IS DECLARED HERE

    void connect();

    long saveResult(const DataSet& data, const SolverResult& result, const std::string& algorithm);

private:
    std::string m_conn_string;
    std::unique_ptr<pqxx::connection> m_connection;

    static std::string to_sql_array(const std::vector<int>& vec);
};
