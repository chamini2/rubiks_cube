#include "HashTable.hpp"

/*
 * type:
 *     0 (default) -> IDA*
 *     1           -> Corners PDB
 *     2           -> Edges PDB
 */
HashTable::HashTable(int type) {
    this->table = new bool[264539520];
    this->type = type;
    this->table_size = 0;

    for (int i = 0; i < 264539520; ++i) {
        this->table[i] = false;
    }
}

HashTable::~HashTable() {
    delete[] table;
}

void HashTable::insert(Cube* cube) {

    int key = rank_it(cube);

    // if ¬(contains(cube))
    if (!table[key]) {
        table[key] = true;
        table_size++;
    }

    // table[key] = key;
}

void HashTable::insert(int key) {

    // if ¬(contains(key))
    if (!table[key]) {
        table[key] = true;
        table_size++;
    }

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

bool HashTable::contains(int key) {

    return table[key];

    // it can only be 1 or 0
    // if (table.count(key) > 0) {
    //     return true;
    // } else {
    //     return false;
    // }
}

bool HashTable::empty() {
    return table_size == 0;
}

int HashTable::size() {
    return table_size;
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
