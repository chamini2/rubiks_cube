#include "HashTable.hpp"

/*
 * type:
 *     0 (default) -> IDA*
 *     1           -> Corners PDB
 *     2           -> Edges PDB
 */
HashTable::HashTable(int type)
    :table(std::vector<bool>(264539520)) {
    this->type = type;
}

// HashTable::~HashTable() {
//     for ( auto it = this->table.begin(); it != this->table.end(); ++it ) {
//         delete[] it->second;
//     }
// }

void HashTable::insert(Cube* cube) {

    int key = rank_it(cube);

    table[key] = true;
    // table[key] = key;
}

bool HashTable::contains(Cube* cube) {

    int key = rank_it(cube);

    return table[key];
    // it can only be 1 or 0
    // if (table.count(key) > 0) {
    //     return true;
    // } else {
    //     return false;
    // }

}

bool HashTable::empty() {
    return table.empty();
}

int HashTable::size() {
    return table.size();
}

////////////////////////////////////////

int HashTable::rank_it(Cube* cube) {
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
