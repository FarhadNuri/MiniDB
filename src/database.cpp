#include "../include/database.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Database::Database() {
    // Constructor - nothing special needed
}

Database::~Database() {
    // Clean up memory
    for (auto& pair : tables) {
        delete pair.second;
    }
}

void Database::executeCommand(const string& command) {
    string cmd = command;
    // Convert to uppercase for easier parsing
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    if (cmd.find("CREATE TABLE") == 0) {
        handleCreateTable(command);
    }
    else if (cmd.find("INSERT") == 0) {
        handleInsert(command);
    }
    else if (cmd.find("SELECT") == 0) {
        handleSelect(command);
    }
    else if (cmd.find("UPDATE") == 0) {
        handleUpdate(command);
    }
    else if (cmd.find("DELETE FROM") == 0) {
        handleDelete(command);
    }
    else {
        cout << "Unknown command: " << command << endl;
        cout << "Type 'HELP' for available commands." << endl;
    }
}

void Database::handleCreateTable(const string& command) {
    // CREATE TABLE users (id, name, email)
    string cmd = command;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    int tablePos = cmd.find("TABLE") + 6;
    int parenPos = command.find('(');
    string tableName = command.substr(tablePos, parenPos - tablePos);
    
    // Remove spaces from table name
    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
    
    int start = command.find('(');
    int end = command.find(')');
    if (start != string::npos && end != string::npos) {
        string colStr = command.substr(start + 1, end - start - 1);
        vector<string> columns = parseColumns(colStr);
        createTable(tableName, columns);
    }
}

void Database::handleInsert(const string& command) {
    // INSERT users VALUES (1, Alice, alice@email.com)
    string cmd = command;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    int tableStart = 6; // after "INSERT"
    int valuesPos = cmd.find("VALUES");
    string tableName = command.substr(tableStart, valuesPos - tableStart);
    
    // Clean table name
    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
    
    int start = command.find('(');
    int end = command.find(')');
    if (start != string::npos && end != string::npos) {
        string valStr = command.substr(start + 1, end - start - 1);
        vector<string> values = parseValues(valStr);
        insertInto(tableName, values);
    }
}

void Database::handleSelect(const string& command) {
    // SELECT * FROM users WHERE name = Alice ORDER BY id
    string cmd = command;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    int fromPos = cmd.find("FROM") + 5;
    int wherePos = cmd.find("WHERE");
    int orderByPos = cmd.find("ORDER BY");
    
    string tableName;
    string whereClause;
    string orderByClause;
    
    if (orderByPos != string::npos) {
        if (wherePos != string::npos && wherePos < orderByPos) {
            tableName = command.substr(fromPos, wherePos - fromPos);
            whereClause = command.substr(wherePos, orderByPos - wherePos);
            orderByClause = command.substr(orderByPos);
        } else {
            tableName = command.substr(fromPos, orderByPos - fromPos);
            orderByClause = command.substr(orderByPos);
        }
    } else if (wherePos != string::npos) {
        tableName = command.substr(fromPos, wherePos - fromPos);
        whereClause = command.substr(wherePos);
    } else {
        tableName = command.substr(fromPos);
    }
    
    // Clean table name
    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
    
    selectFrom(tableName, whereClause, orderByClause);
}

void Database::handleUpdate(const string& command) {
    // UPDATE users SET name = NewName WHERE id = 1
    string cmd = command;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    int setPos = cmd.find("SET");
    int wherePos = cmd.find("WHERE");
    
    if (setPos == string::npos) {
        cout << "Invalid UPDATE syntax. Use: UPDATE table SET column = value WHERE condition" << endl;
        return;
    }
    
    string tableName = command.substr(6, setPos - 6); // Skip "UPDATE"
    string setClause;
    string whereClause;
    
    if (wherePos != string::npos) {
        setClause = command.substr(setPos, wherePos - setPos);
        whereClause = command.substr(wherePos);
    } else {
        setClause = command.substr(setPos);
    }
    
    // Clean table name
    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
    
    updateTable(tableName, setClause, whereClause);
}

void Database::handleDelete(const string& command) {
    // DELETE FROM users WHERE id = 1
    string cmd = command;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    int fromPos = cmd.find("FROM") + 5;
    int wherePos = cmd.find("WHERE");
    
    string tableName;
    string whereClause;
    
    if (wherePos != string::npos) {
        tableName = command.substr(fromPos, wherePos - fromPos);
        whereClause = command.substr(wherePos);
    } else {
        tableName = command.substr(fromPos);
    }
    
    // Clean table name
    tableName.erase(remove_if(tableName.begin(), tableName.end(), ::isspace), tableName.end());
    
    deleteFrom(tableName, whereClause);
}

vector<string> Database::parseColumns(const string& colStr) {
    vector<string> columns;
    stringstream ss(colStr);
    string column;
    
    while (getline(ss, column, ',')) {
        // Remove leading/trailing whitespace
        column.erase(0, column.find_first_not_of(" \t"));
        column.erase(column.find_last_not_of(" \t") + 1);
        columns.push_back(column);
    }
    
    return columns;
}

vector<string> Database::parseValues(const string& valStr) {
    vector<string> values;
    stringstream ss(valStr);
    string value;
    
    while (getline(ss, value, ',')) {
        // Remove leading/trailing whitespace and quotes
        value.erase(0, value.find_first_not_of(" \t'\""));
        value.erase(value.find_last_not_of(" \t'\"") + 1);
        values.push_back(value);
    }
    
    return values;
}

void Database::createTable(const string& tableName, const vector<string>& columns) {
    if (tables.find(tableName) != tables.end()) {
        cout << "Error: Table '" << tableName << "' already exists!" << endl;
        return;
    }
    
    tables[tableName] = new Table(columns);
    cout << "Table '" << tableName << "' created successfully with " << columns.size() << " columns." << endl;
}

void Database::insertInto(const string& tableName, const vector<string>& values) {
    if (tables.find(tableName) == tables.end()) {
        cout << "Error: Table '" << tableName << "' does not exist!" << endl;
        return;
    }
    
    tables[tableName]->insert(values);
    cout << "Row inserted successfully into '" << tableName << "'." << endl;
}

void Database::selectFrom(const string& tableName, const string& whereClause, const string& orderByClause) {
    if (tables.find(tableName) == tables.end()) {
        cout << "Error: Table '" << tableName << "' does not exist!" << endl;
        return;
    }
    
    vector<Row> rows = tables[tableName]->select(whereClause, orderByClause);
    tables[tableName]->printRows(rows);
}

void Database::updateTable(const string& tableName, const string& setClause, const string& whereClause) {
    if (tables.find(tableName) == tables.end()) {
        cout << "Error: Table '" << tableName << "' does not exist!" << endl;
        return;
    }
    
    int updated = tables[tableName]->updateRows(setClause, whereClause);
    cout << updated << " row(s) updated in '" << tableName << "'." << endl;
}

void Database::deleteFrom(const string& tableName, const string& whereClause) {
    if (tables.find(tableName) == tables.end()) {
        cout << "Error: Table '" << tableName << "' does not exist!" << endl;
        return;
    }
    
    int deleted = tables[tableName]->deleteRows(whereClause);
    cout << deleted << " row(s) deleted from '" << tableName << "'." << endl;
}