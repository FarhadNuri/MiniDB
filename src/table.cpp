#include "../include/table.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

Table::Table(const vector<string>& cols) : columns(cols), nextId(1) {
    // Initialize index for each column
    for (const string& col : columns) {
        indexes[col] = SimpleIndex();
    }
}

void Table::insert(const vector<string>& values) {
    if (values.size() != columns.size()) {
        cout << "Error: Expected " << columns.size() << " values, got " << values.size() << endl;
        return;
    }
    
    Row newRow(values, nextId);
    
    // Update indexes
    for (size_t i = 0; i < columns.size(); i++) {
        indexes[columns[i]].insert(values[i], nextId);
    }
    
    rows.push_back(newRow);
    nextId++;
}

vector<Row> Table::select(const string& whereClause, const string& orderByClause) {
    vector<Row> result;
    
    // Apply WHERE clause filtering
    for (const Row& row : rows) {
        if (whereClause.empty() || matchesCondition(row, whereClause)) {
            result.push_back(row);
        }
    }
    
    // Apply ORDER BY sorting
    if (!orderByClause.empty()) {
        sortRows(result, orderByClause);
    }
    
    return result;
}

int Table::deleteRows(const string& whereClause) {
    vector<Row> newRows;
    int deletedCount = 0;
    
    for (const Row& row : rows) {
        if (!whereClause.empty() && matchesCondition(row, whereClause)) {
            // Remove from indexes
            for (size_t i = 0; i < columns.size(); i++) {
                indexes[columns[i]].remove(row.data[i], row.id);
            }
            deletedCount++;
        } else {
            newRows.push_back(row);
        }
    }
    
    rows = newRows;
    return deletedCount;
}

int Table::updateRows(const string& setClause, const string& whereClause) {
    // Parse SET clause: SET column = value
    string upperSet = setClause;
    transform(upperSet.begin(), upperSet.end(), upperSet.begin(), ::toupper);
    
    if (upperSet.find("SET") != 0) {
        return 0;
    }
    
    size_t setPos = 4; // Skip "SET "
    size_t equalPos = setClause.find("=");
    
    if (equalPos == string::npos) {
        return 0;
    }
    
    string column = setClause.substr(setPos, equalPos - setPos);
    string value = setClause.substr(equalPos + 1);
    
    // Clean up column and value
    column.erase(0, column.find_first_not_of(" \t"));
    column.erase(column.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t'\""));
    value.erase(value.find_last_not_of(" \t'\"") + 1);
    
    int colIndex = getColumnIndex(column);
    if (colIndex < 0) {
        return 0;
    }
    
    int updatedCount = 0;
    
    // Update matching rows
    for (Row& row : rows) {
        if (whereClause.empty() || matchesCondition(row, whereClause)) {
            // Update index
            indexes[columns[colIndex]].remove(row.data[colIndex], row.id);
            row.data[colIndex] = value;
            indexes[columns[colIndex]].insert(value, row.id);
            updatedCount++;
        }
    }
    
    return updatedCount;
}

void Table::printRows(const vector<Row>& rowsToPrint) {
    if (rowsToPrint.empty()) {
        cout << "No rows found." << endl;
        return;
    }
    
    // Calculate column widths for better formatting
    vector<size_t> colWidths(columns.size());
    
    // Initialize with header widths
    for (size_t i = 0; i < columns.size(); i++) {
        colWidths[i] = max(columns[i].length(), static_cast<size_t>(8)); // Minimum width of 8
    }
    
    // Check data widths
    for (const Row& row : rowsToPrint) {
        for (size_t j = 0; j < row.data.size(); j++) {
            colWidths[j] = max(colWidths[j], row.data[j].length());
        }
    }
    
    // Print top border
    printBorder(colWidths);
    
    // Print header
    cout << "|";
    for (size_t i = 0; i < columns.size(); i++) {
        cout << " " << left << setw(colWidths[i]) << columns[i] << " |";
    }
    cout << endl;
    
    // Print header separator
    printBorder(colWidths);
    
    // Print data rows
    for (const Row& row : rowsToPrint) {
        cout << "|";
        for (size_t j = 0; j < row.data.size(); j++) {
            cout << " " << left << setw(colWidths[j]) << row.data[j] << " |";
        }
        cout << endl;
    }
    
    // Print bottom border
    printBorder(colWidths);
    
    cout << rowsToPrint.size() << " row(s) returned." << endl;
}

void Table::printBorder(const vector<size_t>& colWidths) {
    cout << "+";
    for (size_t width : colWidths) {
        cout << string(width + 2, '-') << "+";
    }
    cout << endl;
}

bool Table::isNumeric(const string& str) {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') start = 1;
    
    bool hasDecimal = false;
    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false; // Multiple decimal points
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    
    return start < str.length(); // Must have at least one digit
}

bool Table::compareValues(const string& a, const string& b) {
    bool aIsNumeric = isNumeric(a);
    bool bIsNumeric = isNumeric(b);
    
    // If both are numeric, compare as numbers
    if (aIsNumeric && bIsNumeric) {
        double numA = stod(a);
        double numB = stod(b);
        return numA < numB;
    }
    
    // Otherwise, compare as strings
    return a < b;
}

bool Table::matchesCondition(const Row& row, const string& condition) {
    // Simple WHERE clause parsing: WHERE column = value
    string upperCondition = condition;
    transform(upperCondition.begin(), upperCondition.end(), upperCondition.begin(), ::toupper);
    
    if (upperCondition.find("WHERE") != 0) {
        return true;
    }
    
    // Find the column name, operator, and value
    size_t wherePos = upperCondition.find("WHERE") + 6;
    size_t equalPos = condition.find("=");
    
    if (equalPos == string::npos) {
        return false;
    }
    
    string column = condition.substr(wherePos, equalPos - wherePos);
    string value = condition.substr(equalPos + 1);
    
    // Clean up column and value
    column.erase(0, column.find_first_not_of(" \t"));
    column.erase(column.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t'\""));
    value.erase(value.find_last_not_of(" \t'\"") + 1);
    
    int colIndex = getColumnIndex(column);
    if (colIndex < 0) {
        return false;
    }
    
    return row.data[colIndex] == value;
}

void Table::sortRows(vector<Row>& rows, const string& orderByClause) {
    string upperOrderBy = orderByClause;
    transform(upperOrderBy.begin(), upperOrderBy.end(), upperOrderBy.begin(), ::toupper);
    
    if (upperOrderBy.find("ORDER BY") == 0) {
        string columnName = orderByClause.substr(8); // Skip "ORDER BY"
        
        // Clean column name
        columnName.erase(0, columnName.find_first_not_of(" \t"));
        columnName.erase(columnName.find_last_not_of(" \t") + 1);
        
        int colIndex = getColumnIndex(columnName);
        if (colIndex >= 0) {
            sort(rows.begin(), rows.end(), [this, colIndex](const Row& a, const Row& b) {
                return compareValues(a.data[colIndex], b.data[colIndex]);
            });
        }
    }
}

int Table::getColumnIndex(const string& columnName) {
    for (size_t i = 0; i < columns.size(); i++) {
        if (columns[i] == columnName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

size_t Table::getRowCount() const {
    return rows.size();
}

vector<string> Table::getColumnNames() const {
    return columns;
}