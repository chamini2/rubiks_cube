#include <map>
#include "EdgeSet.hpp"

EdgeSet::EdgeSet() {
    this->type = type;
    this->table_size = 0;
}

void EdgeSet::insert(int64_t key) {
// Inserto -1 mientras decidamos qué hacer con eso
    this->table.insert({key, -1});
}

bool EdgeSet::contains(int64_t key) {
    if (this->table.count(key) > 0) {
        return true;
    }

    return false;
}

bool EdgeSet::empty() {
    return table_size == 0;
}

int EdgeSet::size() {
    return table_size;
}

////////////////////////////////////////

int EdgeSet::rank_it(Cube* cube) {
    switch (type) {
        // IDA*
        case 0:
            // int key = rank(?, cube->???());
        // Corners PDB
        case 1:
            return rank(8, cube->get_corners());
        // Edges PDB
        case 2:
            // return rank(12, cube->get_edges());
        default:
            error("rank_it | type = " + int_to_string(type), __LINE__, __FILE__);
            throw -1;
    }
}
