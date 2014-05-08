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

    if (type == 1) {
        // Corners
        this->max_size = 264539520;
    } else if (type == 2) {
        // Edges
        this->max_size = 42577920;
    } else if (type == 3) {
        this->max_size = 510935040;
    }
    this->table = new int8_t[max_size];
    std::fill_n(table, max_size, 127);
}

Set::~Set() {
    delete[] table;
}

void Set::insert(Cube* cube, int8_t level) {
    int key = rank_it(cube);

    if (table[key] == 127) {
        table[key] = level;
        table_size++;
    }
}

void Set::insert(int key, int8_t level) {
    if (table[key] == 127) {
        table[key] = level;
        table_size++;
    }
}

bool Set::contains(Cube* cube) {
    if (table[rank_it(cube)] == 127) {
        return false;
    }

    return true;
}

bool Set::contains(int key) {
    if (table[key] == 127) {
        return false;
    }

    return true;
}

int8_t Set::value(Cube* cube) {
    return table[rank_it(cube)];
}


int8_t Set::value(int key) {
    return table[key];
}

bool Set::empty() {
    return table_size == 0;
}

int Set::size() {
    return table_size;
}

int Set::width() {
    return max_size;
}

////////////////////////////////////////

int Set::rank_it(Cube* cube) {
    switch (type) {
        // IDA*
        case 0:
            // int key = rank(?, cube->???());
        // Corners PDB
        case 1:
            return rank(8, cube->get_corners(), 0, 8, 3);
        // Edges PDB
        case 2:
            return rank(12, cube->get_edges(), 6, 6, 2);
        default:
            error("rank_it | type = " + int_to_string(type), __LINE__, __FILE__);
            throw -1;
    }
}

void Set::print(FILE *file, size_t elem_size) {
    fwrite(table, elem_size, width(), file);
}

void Set::read(FILE *file, size_t elem_size) {
    fread(table, elem_size, width(), file);
}
