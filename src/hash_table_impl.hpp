#ifndef HASH_TABLE_IMPL_HPP
#define HASH_TABLE_IMPL_HPP

#include "hash_table.hpp"

#include <iostream>
#include <mutex>


// Constructor
template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t initial_size) : table(initial_size) {}

// Copy Constructor
template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable& other) {
    std::unique_lock lock(other.mutex);
    table = other.table;
    num_elements = other.num_elements;
    load_factor = other.load_factor;
}

// Copy Assignment Operator
template <typename Key, typename Value>
HashTable<Key, Value>& HashTable<Key, Value>::operator=(const HashTable& other) {
    if (this != &other) {
        std::unique_lock lock1(mutex, std::defer_lock);
        std::unique_lock lock2(other.mutex, std::defer_lock);
        std::lock(lock1, lock2);

        table = other.table;
        num_elements = other.num_elements;
        load_factor = other.load_factor;
    }
    return *this;
}

// Move Constructor
template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(HashTable&& other) noexcept {
    std::unique_lock lock(other.mutex);
    table = std::move(other.table);
    num_elements = other.num_elements;
    load_factor = other.load_factor;
    other.num_elements = 0;
}

// Move Assignment Operator
template <typename Key, typename Value>
HashTable<Key, Value>& HashTable<Key, Value>::operator=(HashTable&& other) noexcept {
    if (this != &other) {
        std::unique_lock lock1(mutex, std::defer_lock);
        std::unique_lock lock2(other.mutex, std::defer_lock);
        std::lock(lock1, lock2);

        table = std::move(other.table);
        num_elements = other.num_elements;
        load_factor = other.load_factor;
        other.num_elements = 0;
    }
    return *this;
}

// Resize Method
template <typename Key, typename Value>
void HashTable<Key, Value>::resize() {
    size_t new_size = table.size() * 2;
    std::vector<std::list<KeyValue>> new_table(new_size);

    for (const auto& bucket : table) {
        for (const auto& kv : bucket) {
            size_t new_index = hash_to_index(compute_hash(kv.key), new_size);
            new_table[new_index].push_back(kv);
        }
    }

    table = std::move(new_table);
}

// Insert Method
template <typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value) {
    std::unique_lock lock(mutex);
    size_t index = hash_to_index(compute_hash(key), table.size());

    for (auto& kv : table[index]) {
        if (kv.key == key) {
            kv.value = value; // Update if key exists
            return;
        }
    }

    table[index].emplace_back(KeyValue{key, value});
    num_elements++;

    if (num_elements > table.size() * load_factor) {
        resize();
    }
}

// Get Method
template <typename Key, typename Value>
std::optional<Value> HashTable<Key, Value>::get(const Key& key) const {
    std::shared_lock lock(mutex);
    size_t index = hash_to_index(compute_hash(key), table.size());

    for (const auto& kv : table[index]) {
        if (kv.key == key) {
            return kv.value;
        }
    }

    return std::nullopt;
}

// Remove Method
template <typename Key, typename Value>
bool HashTable<Key, Value>::remove(const Key& key) {
    std::unique_lock lock(mutex);
    size_t index = hash_to_index(compute_hash(key), table.size());

    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            bucket.erase(it);
            num_elements--;
            return true;
        }
    }

    return false;
}

#endif // HASH_TABLE_IMPL_HPP
