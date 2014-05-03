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
        this->table = new int8_t[264539520];
        std::fill_n(table, 264539520, -1);
    } else if (type == 2) {
        // Edges
        this->table = new int8_t[510935040];
        std::fill_n(table, 264539520, -1);
    }


}

Set::~Set() {
    delete[] table;
}

void Set::insert(Cube* cube, int8_t level) {
    int key = rank_it(cube);

    if (table[key] == -1) {
        table[key] = level;
        table_size++;
    }
}

void Set::insert(int key, int8_t level) {
    if (table[key] == -1) {
        // std::cout << "instertando" << std::endl;
        table[key] = level;
        table_size++;
    }
}

bool Set::contains(Cube* cube) {
    int key = rank_it(cube);

    if (table[key] == -1) {
        return false;
    }

    return true;
}

bool Set::contains(int key) {
    if (table[key] == -1) {
        return false;
    }

    return true;
}

int Set::value(int key) {
    return table[key];
}

bool Set::empty() {
    return table_size == 0;
}

int Set::size() {
    return table_size;
}

int Set::width() {
    if (type == 1) {
        // Corners
        return 264539520;
    } else if (type == 2) {
        // Edges
        return 510935040;
    }

    error("width | type = " + int_to_string(type), __LINE__, __FILE__);
    throw -1;
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
            return rank(12, cube->get_edges(), 7, 3);
        default:
            error("rank_it | type = " + int_to_string(type), __LINE__, __FILE__);
            throw -1;
    }
}
