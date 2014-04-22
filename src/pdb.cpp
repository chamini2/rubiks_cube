#include "HashTable.hpp"
#include <fstream>

void BFS_corners(std::ofstream *file);

void BFS_edges(std::ofstream *file);

int main(int argc, char const *argv[]) {
    std::ofstream file;

    file.open("../pdbs/cPDB.txt");
    BFS_corners(&file);
    file.close();

    file.open("../pdbs/ePDB.txt");
    //BFS_edges(&file);
    file.close();

    return 0;
}

void BFS_corners(std::ofstream *file) {
    std::queue<std::tuple<Cube*,int>> queue;
    std::queue<Cube*> *succ;
    HashTable closed;

    Cube* cube = new Cube;
    int size, level = 0, last_level = -1;
    auto node = std::make_tuple(cube, level);

    queue.push(node);

    while (!queue.empty()) {
        std::tie (cube, level) = queue.front();
        queue.pop();

        if (!closed.contains(cube)) {
            closed.insert(cube);

            if (level != last_level) {
                last_level = level;
                std::cout << "LEVEL " << last_level << std::endl << std::flush;
            }

            if (level == 3) {
                delete cube;
                break;
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
}
