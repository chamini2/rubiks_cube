#include "HashTable.hpp"
#include <fstream>

void BFS_corners(std::ofstream *file);

void BFS_edges(std::ofstream *file);

int main(int argc, char const *argv[]) {
    std::ofstream file ("../pdbs/cPDB.txt");

    BFS_corners(&file);
    file.close();

    file.open("../pdbs/ePDB.txt");
    //BFS_edges(&file);
    file.close();
    return 0;
}

void BFS_corners(std::ofstream *file) {
    std::queue<std::tuple<Cube*,int>> queue;
    HashTable closed;

    Cube* cube = new Cube;
    int level = 0, last_level = -1;
    auto node = std::make_tuple(cube, level);

    queue.push(node);

    while (!queue.empty()) {
        std::tie (cube, level) = queue.front();
        queue.pop();

        // Esto también tiene segmentation fault 11 porque OBVIAMENTE (no?) no
        // está en el hastable
        // if (!closed.contains(cube)) {
            closed.insert(cube);

            if (level != last_level) {
                last_level = level;
                std::cout << "LEVEL " << last_level << std::endl << std::flush;
            }

            (*file) << cube->corners_to_string() << " [" << level << "]\n";

            /*cube->next_corners(&queue, level);*/
            std::queue<Cube*> succ = cube->succ_corners();
            for (int i = 0; i < succ.size(); ++i) {
                cube = succ.front();
                succ.pop();

                node = std::make_tuple(cube, level + 1);
                queue.push(node);
            }
        // }
    }
}
