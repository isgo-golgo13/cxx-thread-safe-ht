#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <list>
#include <optional>
#include <shared_mutex>
#include <string>
#include "hash_function.hpp" // Include the hash function header

template <typename Key, typename Value>
class HashTable {
private:
    struct KeyValue {
        Key key;
        Value value;
    };

    std::vector<std::list<KeyValue>> table; // Buckets for collision handling
    size_t num_elements = 0;                // Number of elements in the hash table
    float load_factor = 0.75;               // Maximum load factor before resizing
    mutable std::shared_mutex mutex;        // Mutex for thread safety

    // Resize the hash table when the load factor is exceeded
    void resize();

public:
    // Constructors and Destructor
    explicit HashTable(size_t initial_size = 16);
    ~HashTable() = default;

    // Rule of Six
    HashTable(const HashTable& other);               // Copy constructor
    HashTable& operator=(const HashTable& other);    // Copy assignment operator
    HashTable(HashTable&& other) noexcept;           // Move constructor
    HashTable& operator=(HashTable&& other) noexcept; // Move assignment operator

    // Public API
    void insert(const Key& key, const Value& value); // Insert key-value pair
    std::optional<Value> get(const Key& key) const;  // Retrieve value by key
    bool remove(const Key& key);                     // Remove key-value pair
};

#include "hash_table_impl.hpp" // Include implementation

#endif // HASH_TABLE_HPP
