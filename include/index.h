#pragma once
#include <vector>
#include <string>

using namespace std;

class SimpleIndex {
private:
    vector<string> keys;    
    vector<int> rowIds;     
    
public:

    void insert(const string& key, int rowId);
    
    vector<int> search(const string& key);

    void remove(const string& key, int rowId);
    
    vector<int> rangeSearch(const string& minKey, const string& maxKey);
    
    size_t size() const;

    void clear();

};
