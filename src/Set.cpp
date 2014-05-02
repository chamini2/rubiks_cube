#include "Set.hpp"
#include <map>

/*
 * type:
 *     0 (default) -> IDA*
 *     1           -> Corners PDB
 *     2           -> Edges 1 PDB
 *     3           -> Edges 2 PDB
 */
Set::Set(int type) {
    this->type = type;
    this->table_size = 0;
    this->table = new bool[264539520];
}

Set::~Set() {
    delete[] table;
}

void Set::insert(Cube* cube) {

    int key = rank_it(cube);

    // if ¬(contains(cube))
    if (!table[key]) {
        table[key] = true;
        table_size++;
    }

    // table[key] = key;
}

void Set::insert(int key) {

    // if ¬(contains(key))
    if (!table[key]) {
        table[key] = true;
        table_size++;
    }

    // table[key] = key;
}

bool Set::contains(Cube* cube) {

    int key = rank_it(cube);

    return table[key];

    // it can only be 1 or 0
    // if (table.count(key) > 0) {
    //     return true;
    // } else {
    //     return false;
    // }
}

bool Set::contains(int key) {

    return table[key];

    // it can only be 1 or 0
    // if (table.count(key) > 0) {
    //     return true;
    // } else {
    //     return false;
    // }
}

bool Set::empty() {
    return table_size == 0;
}

int Set::size() {
    return table_size;
}

////////////////////////////////////////

int Set::rank_it(Cube* cube) {
    switch (type) {
        // IDA*
        case 0:
            // int key = rank(?, cube->???());
        // Corners PDB
        case 1:
            return rank(8, cube->get_corners(), 8, 3);
        // Edges PDB
        case 2:
            // return rank(12, cube->get_edges());
        default:
            error("rank_it | type = " + int_to_string(type), __LINE__, __FILE__);
            throw -1;
    }
}
