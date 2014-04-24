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
        bool *table;
        int type;
        int table_size;

        int rank_it(Cube *cube);
};
