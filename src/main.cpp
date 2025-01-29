#include "hash_table.hpp"

int main() {
    HashTable<std::string, std::string> ht;

    ht.insert("id", "thx138");
    ht.insert("room_id", "1138");
    ht.insert("region", "section 1000");

    if (auto name = ht.get("id")) {
        std::cout << "ID: " << *name << '\n';
    }

    if (auto age = ht.get("room_id")) {
        std::cout << "Room ID: " << *age << '\n';
    }

    if (ht.remove("region")) {
        std::cout << "Region removed successfully.\n";
    }

    if (!ht.get("region")) {
        std::cout << "Region not found.\n";
    }

    return 0;
}
