#include <vector>
#include "Cube.hpp"
#include "rank.hpp"

class Set {
    public:
        Set(int type = 0); // defaults to IDA*
        ~Set();

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


