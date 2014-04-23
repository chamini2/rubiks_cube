#include "HashTable.hpp"

HashTable::HashTable() {}

// HashTable::~HashTable() {
//     for ( auto it = this->table.begin(); it != this->table.end(); ++it ) {
//         delete[] it->second;
//     }
// }

void HashTable::insert(Cube* cube) {
    // IDA*
    // int key = rank(?, cube->???());

    // corner PDB
    int key = rank(8, cube->get_corners());

    // edge PDB
    // int key = rank(12, cube->get_edges());

    this->table.emplace(key,key);
}

bool HashTable::contains(Cube* cube) {
    // IDA*
    // int key = rank(?, cube->???());

    // corner PDB
    int key = rank(8, cube->get_corners());

    // edge PDB
    // int key = rank(12, cube->get_edges());

    auto range = this->table.equal_range(key);

    if (range.first == this->table.end()) {
        return false;

    // If the else happens, since now the hash is unique, we can immediatly say 'true'
    // though we should check that this is the ONLY element in the iterator (IDK how to)
    } else {
        // while (range.first != range.second) {
        //     if (cube->equals_corners(range.first->second)) {
        //         return true;
        //     }

        //     range.first++;
        // }
        return true;
    }

    return false;
}

bool HashTable::empty() {
    return this->size() == 0;
}

int HashTable::size() {
    return this->table.size();
}
