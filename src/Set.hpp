#include <vector>
#include "Cube.hpp"
#include "rank.hpp"

class Set {
    public:
        Set(int type = 0); // defaults to IDA*
        ~Set();

        void insert(Cube* cube, int8_t level);
        void insert(int key, int8_t level);
        bool contains(Cube* cube);
        bool contains(int key);
        int value(int key);
        bool empty();
        int size();
        int width();

    private:
        int8_t *table;
        int type;
        int table_size;

        int rank_it(Cube *cube);
};


