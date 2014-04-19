#include <unordered_map>
#include "Cube.hpp"

class HashTable {

public:
  HashTable();
  ~HashTable();
  void insert(Cube*);
  bool contains(Cube*);
  int size();
  
private:
  std::unordered_map<std::string,Cube*> table;
};
