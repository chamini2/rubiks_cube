#include "HashTable.hpp"

HashTable::HashTable(){}

void HashTable::insert(Cube* cube){
  std::string key = cube->to_string();
  this->table.emplace(key,cube);
}

bool HashTable::contains(Cube* cube){
  std::string key = cube->to_string();
  Cube* cube_obtained;
  cube_obtained = this->table[key]; 
  if (cube->equals(cube_obtained))
    return true;
  else
    return false;
}

int HashTable::size(){
  return this->table.size();
}
