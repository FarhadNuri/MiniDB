#pragma once
#include <string>
#include <map>
#include <vector>
#include "table.h"

using namespace std;

/**
 * @brief Main Database Engine class that manages multiple tables and SQL command execution
 * 
 * The Database class serves as the primary interface for the in-memory database engine.
 * It handles SQL command parsing, table management, and coordinates operations across tables.
 */
class Database {
private:
    map<string, Table*> tables;  ///< Map of table names to Table objects
    
    // Command parsing helpers
    void handleCreateTable(const string& command);
    void handleInsert(const string& command);
    void handleSelect(const string& command);
    void handleUpdate(const string& command);
    void handleDelete(const string& command);
    
    // Utility functions
    vector<string> parseColumns(const string& colStr);
    vector<string> parseValues(const string& valStr);
    
public:
    /**
     * @brief Construct a new Database object
     */
    Database();
    
    /**
     * @brief Destroy the Database object and clean up memory
     */
    ~Database();
    
    /**
     * @brief Execute a SQL command
     * @param command The SQL command string to execute
     */
    void executeCommand(const string& command);
    
    /**
     * @brief Create a new table with specified columns
     * @param tableName Name of the table to create
     * @param columns Vector of column names
     */
    void createTable(const string& tableName, const vector<string>& columns);
    
    /**
     * @brief Insert values into a table
     * @param tableName Name of the target table
     * @param values Vector of values to insert
     */
    void insertInto(const string& tableName, const vector<string>& values);
    
    /**
     * @brief Select data from a table with optional conditions
     * @param tableName Name of the source table
     * @param whereClause Optional WHERE clause for filtering
     * @param orderByClause Optional ORDER BY clause for sorting
     */
    void selectFrom(const string& tableName, const string& whereClause = "", const string& orderByClause = "");
    
    /**
     * @brief Delete rows from a table
     * @param tableName Name of the target table
     * @param whereClause Optional WHERE clause for filtering
     */
    void deleteFrom(const string& tableName, const string& whereClause);
    
    /**
     * @brief Update rows in a table
     * @param tableName Name of the target table
     * @param setClause SET clause specifying column=value
     * @param whereClause Optional WHERE clause for filtering
     */
    void updateTable(const string& tableName, const string& setClause, const string& whereClause);
    
    /**
     * @brief Get the number of tables in the database
     * @return Number of tables
     */
    size_t getTableCount() const { return tables.size(); }
    
    /**
     * @brief Check if a table exists
     * @param tableName Name of the table to check
     * @return true if table exists, false otherwise
     */
    bool tableExists(const string& tableName) const {
        return tables.find(tableName) != tables.end();
    }
};