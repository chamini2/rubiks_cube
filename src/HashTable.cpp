#include "HashTable.hpp"

HashTable::HashTable(){}

void HashTable::insert(Cube* cube){
    // IDA*
    // std::string key = cube->to_string();

    // corner PDB
    std::string key = cube->corners_to_string();

    // edge PDB
    // std::string key = cube->edges_to_string();
    this->table.emplace(key,cube);
}

bool HashTable::contains(Cube* cube){
    // IDA*
    // std::string key = cube->to_string();

    // corner PDB
    std::string key = cube->corners_to_string();

    // edge PDB
    // std::string key = cube->edges_to_string();
    auto range = this->table.equal_range(key);

    if (range.first == this->table.end()){
        return false;
    } else {
        while (range.first != range.second) {
            if (range.first->second->equals(cube)){
                return true;
            }

            range.first++;
        }
    }

    return false;
}

bool HashTable::empty() {
    return this->size() == 0;
}

int HashTable::size() {
    return this->table.size();
}
