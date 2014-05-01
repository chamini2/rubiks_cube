#include <vector>
#include "Cube.hpp"

class HashTable {

    public:
        HashTable(int type = 0); // defaults to IDA*
        ~HashTable();

        void insert(Cube*);
        void insert(int);
        bool contains(Cube*);
        bool contains(int);
        bool empty();
        int size();

    private:
        bool *table;
        int type;
        int table_size;

        int rank_it(Cube *cube);
};
