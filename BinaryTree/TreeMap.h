#ifndef ADS_2024_CA2_ALEXANDRU_RADU_TREEMAP_H
#define ADS_2024_CA2_ALEXANDRU_RADU_TREEMAP_H

#include "BinaryTree.h"
#include <vector>
#include <utility>
#include <stdexcept>

template <typename K, typename V>
class TreeMap {
private:
    BinaryTree<std::pair<K, V>> tree; // BinaryTree to store key-value pairs
    int mapSize;                      // Track the number of key-value pairs

public:
    // Constructor
    TreeMap() : mapSize(0) {}

    // Removes all entries from the map
    void clear() {
        tree.clear();
        mapSize = 0;
    }

    // Returns true if the map contains the specified key
    bool containsKey(const K& key) const {
        return tree.find(std::make_pair(key, V())) != nullptr;
    }

    // Returns the value associated with the key
    V& get(const K& key) const {
        auto found = tree.find(std::make_pair(key, V()));
        if (found == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return found->second;
    }

    // Returns a vector of all keys
    std::vector<K> keySet() const {
        std::vector<K> keys;
        auto allPairs = tree.inOrderTraversal();
        for (const auto& pair : allPairs) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Associates a value with a key
    V& put(const K& key, const V& value) {
        auto node = tree.find(std::make_pair(key, V()));
        if (node == nullptr) {
            tree.add(std::make_pair(key, value));
            mapSize++;
            node = tree.find(std::make_pair(key, V())); // Ensure node is not null after add
        } else {
            node->second = value; // Update the value if the key already exists
        }
        return node->second;
    }

    // Returns the number of key-value pairs
    int size() const {
        return mapSize;
    }

    // Removes a key from the map
    bool removeKey(const K& key) {
        if (containsKey(key)) {
            tree.remove(std::make_pair(key, V()));
            mapSize--;
            return true;
        }
        return false;
    }

    // Accesses or inserts a default value for a key
    V& operator[](const K& key) {
        auto node = tree.find(std::make_pair(key, V()));
        if (node == nullptr) {
            V newValue;
            put(key, newValue);
            node = tree.find(std::make_pair(key, V()));
        }
        return node->second;
    }
};

#endif // ADS_2024_CA2_ALEXANDRU_RADU_TREEMAP_H