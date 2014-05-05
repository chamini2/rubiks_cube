#include <fstream>
#include "Set.hpp"

void BFS_corners(FILE *file, int end);

void BFS_edges1(FILE *file, int end);

void BFS_edges2(FILE *file, int end);

int main(int argc, char const *argv[]) {
    FILE *file;
    int end = -1;

    if (argc > 1) {
        end = 1 + atoi(argv[1]);
    }

    // file = fopen("../pdbs/cPDB.bin", "wb");
    // if (file == NULL) {
    //     error("main | file cPDB did not open correctly", __LINE__, __FILE__);
    // }
    // BFS_corners(file, end);
    // fclose(file);

    file = fopen("../pdbs/e1PDB.bin", "w");
    if (file == NULL) {
        error("main | file cPDB did not open correctly", __LINE__, __FILE__);
    }
    BFS_edges1(file, end);
    fclose(file);

    return 0;
}

void BFS_corners(FILE *file, int end) {
    std::queue<std::tuple<int, int, int8_t>> queue;     // <rank, last, level>
    std::queue<Cube*> *succ;
    Set closed(1);

    Cube* cube = new Cube;
    int info, size;
    int8_t level = 0, last_level = -1;
    int *corners;
    int last;
    std::tuple<int, int, int8_t> node;

    std::cout << "starting cPDB\n" << std::flush;

    corners = cube->get_corners();
    info = rank(8, corners, 8, 3);
    last = cube->get_last();

    node = std::make_tuple(info, last, level);

    queue.push(node);

    closed.insert(info, level);

    delete cube;

    while (!queue.empty()) {
        std::tie(info, last, level) = queue.front();
        queue.pop();

        cube = new Cube(info, 0, last);

        if (level == end) {
            delete cube;
            break;
        }

        if (level != last_level) {
            last_level = level;
            std::cout << "LEVEL " << int_to_string(last_level) << " | queue " << queue.size();
            std::cout << " | closed " << closed.size() << std::endl;
            std::cout << std::flush;
        }

        succ = cube->succ();
        size = succ->size();

        delete cube;

        for (int i = 0; i < size; ++i) {
            cube = succ->front();
            succ->pop();

            corners = cube->get_corners();
            info = rank(8, corners, 8, 3);
            last = cube->get_last();

            if (!closed.contains(info)) {
                node = std::make_tuple(info, last, level + 1);

                queue.push(node);
                closed.insert(info, level);
            }

            delete cube;
        }

        delete succ;
    }

    // if the 'end' argument was modified
    while (!queue.empty()) {
        std::tie(info, last, level) = queue.front();

        queue.pop();
    }

    //binary write, all at once
    closed.print(file,1);

    std::cout << "ending cPDB\n";
}

void BFS_edges1(FILE *file, int end) {
    std::queue<std::tuple<Cube*, int8_t>> queue;     // <rank, last, level>
    std::queue<Cube*> *succ;
    Set closed(2);

    Cube* cube = new Cube;
    int info, size;
    int8_t level = 0, last_level = -1;
    int *edges;
    std::tuple<Cube*, int8_t> node;

    std::cout << "starting e1PDB\n" << std::flush;

    edges = cube->get_edges();
    info = rank(12, edges, 6, 2);

    node = std::make_tuple(cube, level);

    queue.push(node);

    closed.insert(info, level);

    while (!queue.empty()) {
        std::tie(cube, level) = queue.front();
        queue.pop();

        if (level == end) {
            delete cube;
            break;
        }

        if (level != last_level) {
            last_level = level;
            std::cout << "LEVEL " << int_to_string(last_level) << " | queue " << queue.size();
            std::cout << " | closed " << closed.size() << std::endl;
            std::cout << std::flush;
        }

        edges = cube->get_edges();
        fprintf(file, "%s %d\n", array_to_string(edges, 12).c_str(), info);
        delete edges;

        succ = cube->succ();
        size = succ->size();

        delete cube;

        for (int i = 0; i < size; ++i) {
            cube = succ->front();
            succ->pop();

            edges = cube->get_edges();
            info = rank(12, edges, 6, 2);

            if (!closed.contains(info)) {
                node = std::make_tuple(cube, level + 1);
                queue.push(node);
                closed.insert(info, level);
            } else {
                delete cube;
            }
        }

        delete succ;
    }

    // if the 'end' argument was modified
    while (!queue.empty()) {
        std::tie(cube, level) = queue.front();
        queue.pop();

        delete cube;
    }

    //binary write, all at once
    // closed.print(file,1); ///////////////////////////////

    std::cout << "ending e1PDB\n";
}
