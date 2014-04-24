#include <fstream>
#include "HashTable.hpp"

void BFS_corners(std::ofstream *file, int end);

void BFS_edges(std::ofstream *file);

int main(int argc, char const *argv[]) {
    std::ofstream file;
    int end = -1;

    if (argc > 1) {
        end = 1 + atoi(argv[1]);
    }

    file.open("../pdbs/cPDB.txt");
    BFS_corners(&file, end);
    file.close();

    file.open("../pdbs/ePDB.txt");
    //BFS_edges(&file);
    file.close();

    return 0;
}

void BFS_corners(std::ofstream *file, int end) {
    std::queue<std::tuple<int,char,int>> queue;
    std::queue<Cube*> *succ;
    HashTable *closed =  new HashTable(1);

    Cube* cube = new Cube;
    int info, size, level = 0, last_level = -1;
    int *corners = cube->get_corners();
    char last = cube->get_last();
    auto node = std::make_tuple(rank(8,corners), last, level);

    delete cube;

    queue.push(node);

    while (!queue.empty()) {
        std::tie (info, last, level) = queue.front();
        queue.pop();

        cube = new Cube(info, 0, last);

        if (!closed->contains(cube)) {
            closed->insert(cube);

            if (level == end) {
                delete cube;
                break;
            }

            if (level != last_level) {
                last_level = level;
                std::cout << "LEVEL " << last_level << std::endl << std::flush;
            }

            (*file) << cube->corners_to_string() << " [" << level << "]\n";

            succ = cube->succ();
            size = succ->size();

            delete cube;

            for (int i = 0; i < size; ++i) {
                cube = succ->front();
                succ->pop();
                if (!closed->contains(cube)) {
                    corners = cube->get_corners();
                    info = rank(8, corners);
                    last = cube->get_last();
                    node = std::make_tuple(info, last, level+1);

                    queue.push(node);
                }

                delete cube;
            }

            delete succ;
        } else {
            delete cube;
        }
    }

    while (!queue.empty()) {
        std::tie (info, last, level) = queue.front();

        queue.pop();
    }

    delete closed;
}
