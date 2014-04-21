#include <unordered_map>
#include "Cube.hpp"
#include <iterator>

class HashTable {
  
public:
  HashTable();
  ~HashTable();
  void insert(Cube*);
  bool contains(Cube*);
  int size();
  
private:
  std::unordered_multimap<std::string, Cube*> table;
};
