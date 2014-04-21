#include "HashTable.hpp"

HashTable::HashTable(){}

void HashTable::insert(Cube* cube){
    std::string key = cube->to_string();
    this->table.emplace(key,cube);
}

bool HashTable::contains(Cube* cube){
    std::string key = cube->to_string();
    auto rango = this->table.equal_range(key);

    if (rango.first == this->table.end())
        return false;
    else
        while (rango.first != rango.second) {
            if (rango.first->second == cube)
                return true;

            rango.first++;
        }

    return false;
}

bool HashTable::empty() {
    return this->size() == 0;
}

int HashTable::size() {
    return this->table.size();
}
