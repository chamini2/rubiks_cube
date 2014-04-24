#include <vector>
#include "Cube.hpp"
#include "rank.hpp"

class HashTable {

    public:
        HashTable(int type = 0); // defaults to IDA*
        // ~HashTable();

        void insert(Cube*);
        bool contains(Cube*);
        bool empty();
        int size();

    private:
        std::vector<bool> table;
        int type;

        int rank_it(Cube *cube);
};
