#ifndef HASH_FUNCTION_HPP
#define HASH_FUNCTION_HPP

#include <string>
#include <format>
#include <blake3.h>

// Computes the Blake3 hash for the given input
std::string compute_hash(const std::string& input);

// Maps hash to an integer index
size_t hash_to_index(const std::string& hash, size_t table_size);

#endif // HASH_FUNCTION_HPP
