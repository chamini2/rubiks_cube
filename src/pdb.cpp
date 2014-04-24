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
    std::queue<std::tuple<Cube*,int>> queue;
    std::queue<Cube*> *succ;
    HashTable *closed =  new HashTable(1);

    Cube* cube = new Cube;
    int size, level = 0, last_level = -1;
    auto node = std::make_tuple(cube, level);

    queue.push(node);

    while (!queue.empty()) {
        std::tie (cube, level) = queue.front();
        queue.pop();

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

            /*cube->next_corners(&queue, level);*/
            succ = cube->succ();
            size = succ->size();

            delete cube;

            for (int i = 0; i < size; ++i) {
                cube = succ->front();
                succ->pop();

                node = std::make_tuple(cube, level+1);
                queue.push(node);
            }

            delete succ;
        } else {
            delete cube;
        }
    }

    while (!queue.empty()) {
        std::tie (cube, level) = queue.front();

        queue.pop();

        delete cube;
    }

    delete closed;
}
