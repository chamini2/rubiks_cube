#include <bitset>
#include "HashTable.hpp"

void BFS_corners(FILE *file, int end);

void BFS_edges(FILE *file);

int main(int argc, char const *argv[]) {
    FILE *file;
    int end = -1;

    if (argc > 1) {
        end = 1 + atoi(argv[1]);
    }

    file = fopen("../pdbs/cPDB.bin", "wb");
    if (file == NULL) {
        error("main | file cPDB did not open correctly", __LINE__, __FILE__);
    }
    BFS_corners(file, end);
    fclose(file);

    // file.open("../pdbs/ePDB.txt");
    // BFS_edges(&file);
    // file.close();

    return 0;
}

void BFS_corners(FILE *file, int end) {
    std::queue<std::tuple<int, int, int>> queue;
    std::queue<Cube*> *succ;
    HashTable closed(1);

    Cube* cube = new Cube;
    int info, size, last_level = -1;
    uint8_t level = 0;
    int *corners;
    int last;
    std::tuple<int, int, int> node;

    std::cout << "starting cPDB\n" << std::flush;

    corners = cube->get_corners();
    info = rank(8,corners);
    last = cube->get_last();

    node = std::make_tuple(info, last, level);

    queue.push(node);
    closed.insert(cube);
    delete cube;

    while (!queue.empty()) {
        std::tie (info, last, level) = queue.front();
        queue.pop();

        cube = new Cube(info, 0, last);

        if (level == end) {
            delete cube;
            break;
        }

        if (level != last_level) {
            last_level = level;
            std::cout << "LEVEL " << last_level << " | queue " << queue.size() << " | closed " << closed.size() << "\n" << std::flush;
        }

        // binary write
        fwrite(&level, 1, 1, file);
        fwrite(&info , 4, 1, file);

        succ = cube->succ();
        size = succ->size();

        delete cube;

        for (int i = 0; i < size; ++i) {
            cube = succ->front();
            succ->pop();

            corners = cube->get_corners();
            info = rank(8, corners);
            last = cube->get_last();

            if (!closed.contains(info)) {
                node = std::make_tuple(info, last, level+1);

                queue.push(node);
                closed.insert(cube);
            }

            delete cube;
        }

        delete succ;
    }

    while (!queue.empty()) {
        std::tie(info, last, level) = queue.front();

        queue.pop();
    }

    std::cout << "ending cPDB\n";
}
