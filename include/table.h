#pragma once
#include <vector>
#include <string>
#include <map>
#include "index.h"

using namespace std;

struct Row {
    vector<string> data; 
    int id;              
    
    Row(const vector<string>& d, int rowId) : data(d), id(rowId) {}
};

class Table {
private:
    vector<string> columns;          
    vector<Row> rows;              
    map<string, SimpleIndex> indexes; 
    int nextId;                     
    
    bool matchesCondition(const Row& row, const string& condition);

    void sortRows(vector<Row>& rows, const string& orderByClause);

    int getColumnIndex(const string& columnName);

    void printBorder(const vector<size_t>& colWidths);

    bool isNumeric(const string& str);

    bool compareValues(const string& a, const string& b);
    
public:

    Table(const vector<string>& cols);

    void insert(const vector<string>& values);

    vector<Row> select(const string& whereClause = "", const string& orderByClause = "");

    int deleteRows(const string& whereClause);

    int updateRows(const string& setClause, const string& whereClause);
    
    void printRows(const vector<Row>& rows);
  
    vector<string> getColumnNames() const;

    size_t getRowCount() const;

};
