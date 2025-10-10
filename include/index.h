#pragma once
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Simple index structure for fast data lookups
 * 
 * This class provides a lightweight indexing mechanism for database columns.
 * While not a full B-Tree implementation, it offers efficient search capabilities
 * for equality and range queries.
 * 
 * Performance Characteristics:
 * - Insert: O(1)
 * - Search: O(n) - Linear search through keys
 * - Delete: O(n) - Linear search to find and remove
 * - Range Search: O(n) - Linear scan with filtering
 * 
 * Future Enhancement: Could be replaced with a proper B-Tree for O(log n) operations
 */
class SimpleIndex {
private:
    vector<string> keys;    ///< Indexed key values
    vector<int> rowIds;     ///< Corresponding row IDs
    
public:
    /**
     * @brief Insert a key-value pair into the index
     * @param key The key to index
     * @param rowId The corresponding row ID
     */
    void insert(const string& key, int rowId);
    
    /**
     * @brief Search for all row IDs matching a key
     * @param key The key to search for
     * @return Vector of matching row IDs
     */
    vector<int> search(const string& key);
    
    /**
     * @brief Remove a specific key-rowId pair from the index
     * @param key The key to remove
     * @param rowId The specific row ID to remove
     */
    void remove(const string& key, int rowId);
    
    /**
     * @brief Perform a range search between two keys (inclusive)
     * @param minKey Minimum key value
     * @param maxKey Maximum key value
     * @return Vector of row IDs within the range
     */
    vector<int> rangeSearch(const string& minKey, const string& maxKey);
    
    /**
     * @brief Get the number of entries in the index
     * @return Number of key-value pairs
     */
    size_t size() const;
    
    /**
     * @brief Clear all entries from the index
     */
    void clear();
};