#pragma once
#include <vector>
#include <string>
#include <map>
#include "index.h"

using namespace std;

/**
 * @brief Represents a single row in a table
 */
struct Row {
    vector<string> data;  ///< Column values for this row
    int id;              ///< Unique row identifier
    
    /**
     * @brief Construct a new Row object
     * @param d Column data
     * @param rowId Unique identifier
     */
    Row(const vector<string>& d, int rowId) : data(d), id(rowId) {}
};

/**
 * @brief Table class that manages rows, columns, and indexes
 * 
 * The Table class represents a database table with support for:
 * - Column-based data storage
 * - Automatic indexing for fast lookups
 * - CRUD operations (Create, Read, Update, Delete)
 * - Query filtering and sorting
 */
class Table {
private:
    vector<string> columns;           ///< Column names
    vector<Row> rows;                ///< Table data
    map<string, SimpleIndex> indexes; ///< Column indexes for fast lookups
    int nextId;                      ///< Next available row ID
    
    /**
     * @brief Check if a row matches a WHERE condition
     * @param row Row to check
     * @param condition WHERE clause condition
     * @return true if row matches condition
     */
    bool matchesCondition(const Row& row, const string& condition);
    
    /**
     * @brief Sort rows based on ORDER BY clause
     * @param rows Rows to sort (modified in place)
     * @param orderByClause ORDER BY clause
     */
    void sortRows(vector<Row>& rows, const string& orderByClause);
    
    /**
     * @brief Get column index by name
     * @param columnName Name of the column
     * @return Column index or -1 if not found
     */
    int getColumnIndex(const string& columnName);
    
    /**
     * @brief Print table border for formatted output
     * @param colWidths Column widths for formatting
     */
    void printBorder(const vector<size_t>& colWidths);
    
    /**
     * @brief Check if a string represents a numeric value
     * @param str String to check
     * @return true if string is numeric
     */
    bool isNumeric(const string& str);
    
    /**
     * @brief Compare two values intelligently (numeric vs string)
     * @param a First value
     * @param b Second value
     * @return true if a < b
     */
    bool compareValues(const string& a, const string& b);
    
public:
    /**
     * @brief Construct a new Table object
     * @param cols Column names for the table
     */
    Table(const vector<string>& cols);
    
    /**
     * @brief Insert a new row into the table
     * @param values Column values for the new row
     */
    void insert(const vector<string>& values);
    
    /**
     * @brief Select rows from the table with optional filtering and sorting
     * @param whereClause Optional WHERE clause for filtering
     * @param orderByClause Optional ORDER BY clause for sorting
     * @return Vector of matching rows
     */
    vector<Row> select(const string& whereClause = "", const string& orderByClause = "");
    
    /**
     * @brief Delete rows matching the WHERE clause
     * @param whereClause WHERE clause for filtering rows to delete
     * @return Number of rows deleted
     */
    int deleteRows(const string& whereClause);
    
    /**
     * @brief Update rows matching the WHERE clause
     * @param setClause SET clause specifying column=value
     * @param whereClause WHERE clause for filtering rows to update
     * @return Number of rows updated
     */
    int updateRows(const string& setClause, const string& whereClause);
    
    /**
     * @brief Print rows in a formatted table
     * @param rows Rows to print
     */
    void printRows(const vector<Row>& rows);
    
    /**
     * @brief Get column names
     * @return Vector of column names
     */
    vector<string> getColumnNames() const;
    
    /**
     * @brief Get number of rows in the table
     * @return Row count
     */
    size_t getRowCount() const;
};