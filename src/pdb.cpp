#include "pdb.hpp"

void BFS(FILE *file, int end, int type, int n, int low, int quan, int factor);

void get_pdb(int which) {
    FILE *file;
    int end = -1;

    switch(which) {
        case(1):
            file = fopen("../pdbs/cPDB.bin", "wb");
            if (file == NULL) {
                error("main | file cPDB did not open correctly", __LINE__, __FILE__);
            }
            BFS(file, end, 1, 8, 0, 8, 3);
            fclose(file);
            break;
        case(2):
            file = fopen("../pdbs/e1PDB.bin", "wb");
            if (file == NULL) {
                error("main | file e1PDB did not open correctly", __LINE__, __FILE__);
            }
            BFS(file, end, 2, 12, 6, 6, 2);
            fclose(file);
            break;
        case(3):
            file = fopen("../pdbs/e2PDB.bin", "wb");
            if (file == NULL) {
                error("main | file e2PDB did not open correctly", __LINE__, __FILE__);
            }
            BFS(file, end, 3, 12, 0, 6, 2);
            fclose(file);
            break;
    }
}

void BFS(FILE *file, int end, int type, int n, int low, int quan, int factor) {
    std::queue<std::tuple<int, int, int8_t>> queue;     // <rank, last, level>
    std::queue<Cube*> *succ;
    Set closed(type);

    Cube* cube = new Cube;
    int info, size;
    int8_t level = 0, last_level = -2;
    int *array;
    int last;
    std::tuple<int, int, int8_t> node;

    std::cout << "starting PDB\n" << std::flush;

    if (type == 1) {
        array = cube->get_corners();
    } else {
        array = cube->get_edges();
    }
    info = rank(n, array, low, quan, factor);
    last = cube->get_last();

    node = std::make_tuple(info, last, level);

    queue.push(node);

    closed.insert(info, level);

    delete cube;

    while (!queue.empty()) {
        std::tie(info, last, level) = queue.front();
        queue.pop();

        if (type == 1) {
            // Corners
            cube = new Cube(info, 0, last, low, quan);
        } else {
            // Edges
            cube = new Cube(0, info, last, low, quan);
        }

        if (last_level == end) {
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

            if (type == 1) {
                array = cube->get_corners();
            } else {
                array = cube->get_edges();
            }
            info = rank(n, array, low, quan, factor);
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

    std::cout << "ending PDB\n";
}
