#include "hash_function.hpp"

// Compute BLAKE3 hash
std::string compute_hash(const std::string& input) {
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, input.data(), input.size());

    uint8_t output[BLAKE3_OUT_LEN];
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

    std::string hex_output;
    for (size_t i = 0; i < BLAKE3_OUT_LEN; ++i) {
        hex_output += std::format("{:02x}", output[i]);
    }
    return hex_output;
}

// Convert hash to index
size_t hash_to_index(const std::string& hash, size_t table_size) {
    size_t index = 0;
    for (char c : hash) {
        index = (index * 31 + c) % table_size;
    }
    return index;
}
