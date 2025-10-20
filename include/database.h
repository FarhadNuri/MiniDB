#pragma once
#include <string>
#include <map>
#include <vector>
#include "table.h"

using namespace std;

class Database {
private:
    map<string, Table*> tables;  ///< Map of table names to Table objects
    
    
    void handleCreateTable(const string& command);
    void handleInsert(const string& command);
    void handleSelect(const string& command);
    void handleUpdate(const string& command);
    void handleDelete(const string& command);
    
    
    vector<string> parseColumns(const string& colStr);
    vector<string> parseValues(const string& valStr);
    
public:

    Database();

    ~Database();
    
    void executeCommand(const string& command);
    
    void createTable(const string& tableName, const vector<string>& columns);
    
    void insertInto(const string& tableName, const vector<string>& values);
    
    void selectFrom(const string& tableName, const string& whereClause = "", const string& orderByClause = "");
    
    void deleteFrom(const string& tableName, const string& whereClause);
    
    void updateTable(const string& tableName, const string& setClause, const string& whereClause);

    size_t getTableCount() const { return tables.size(); }

    bool tableExists(const string& tableName) const {
        return tables.find(tableName) != tables.end();
    }

};

