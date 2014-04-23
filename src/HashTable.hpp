#include <unordered_map>
#include <iterator>
#include "Cube.hpp"
#include "rank.hpp"

class HashTable {

    public:
        HashTable();
        // ~HashTable();

        void insert(Cube*);
        bool contains(Cube*);
        bool empty();
        int size();

    private:
        std::unordered_multimap<int,int> table;
};
