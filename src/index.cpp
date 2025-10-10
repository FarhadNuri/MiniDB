#include "../include/index.h"
#include <algorithm>

using namespace std;

void SimpleIndex::insert(const string& key, int rowId) {
    keys.push_back(key);
    rowIds.push_back(rowId);
}

vector<int> SimpleIndex::search(const string& key) {
    vector<int> result;
    
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            result.push_back(rowIds[i]);
        }
    }
    
    return result;
}

void SimpleIndex::remove(const string& key, int rowId) {
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key && rowIds[i] == rowId) {
            keys.erase(keys.begin() + i);
            rowIds.erase(rowIds.begin() + i);
            break;
        }
    }
}

vector<int> SimpleIndex::rangeSearch(const string& minKey, const string& maxKey) {
    vector<int> result;
    
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] >= minKey && keys[i] <= maxKey) {
            result.push_back(rowIds[i]);
        }
    }
    
    // Sort results by row ID for consistent ordering
    sort(result.begin(), result.end());
    
    return result;
}

size_t SimpleIndex::size() const {
    return keys.size();
}

void SimpleIndex::clear() {
    keys.clear();
    rowIds.clear();
}