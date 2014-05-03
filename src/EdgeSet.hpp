#include <vector>
#include <map>
#include "Cube.hpp"
#include "rank.hpp"

class EdgeSet {
    public:
        EdgeSet();  // defaults to IDA*
        ~EdgeSet();

        void insert(int64_t info);
        bool contains(int64_t info);
        bool empty();
        int size();

    private:
        std::map<int64_t, int> table;
        int type;
        int table_size;

        int rank_it(Cube *cube);
};
