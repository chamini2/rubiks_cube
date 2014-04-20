#include "HashTable.hpp"

HashTable::HashTable(){}

void HashTable::insert(Cube* cube){
    std::string key = cube->to_string();
    this->table.emplace(key,cube);
}

bool HashTable::contains(Cube* cube){
    std::string key = cube->to_string();
    Cube* cube_obtained = this->table[key];

    // CHECAR SI this->table[key] funcionó primero
    if (cube->equals(cube_obtained))
        return true;
    else
        return false;
}

bool HashTable::empty() {
    return this->size() == 0;
}

int HashTable::size(){
    return this->table.size();
}
