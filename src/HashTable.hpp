#include <unordered_map>
#include "Cube.hpp"

class HashTable {
    public:
        HashTable();

        void insert(Cube* cube);
        bool contains(Cube* cube);
        int size();

    private:
        std::unordered_map<std::string, Cube*> table;
};
