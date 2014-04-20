#include "HashTable.hpp"
#include <tuple>

int main(int argc, char const *argv[])
{
    BFS();
    return 0;
}

void BFS() {
    std::queue<std::tuple<Cube*,int>> queue;
    HashTable closed;

    Cube* cube = new Cube;
    int level = 0;
    auto node = std::make_tuple(cube, level)

    queue.push(node);

    while (!queue.empty()) {
        std::tie (cube, level) = queue.front();
        queue.pop();

        if (!closed.contains(cube)) {
            closed.insert(cube);

            std::cout << cube.printable() << " " << level;

            cube->next_corners(&queue);
        }
    }
}
