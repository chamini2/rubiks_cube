#include <unordered_map>
#include "Cube.hpp"

class HashTable {

public:
    HashTable();

    void insert(Cube*);
    bool contains(Cube*);
    bool empty();
    int size();

private:
    std::unordered_map<std::string,Cube*> table;
};
