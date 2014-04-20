#include "HashTable.hpp"

int main(int argc, char const *argv[])
{
    std::queue<std::tuple<Cube*,int>> queue;
    HashTable hash;

    Cube* cube = new Cube;
    int level = 0;
    auto node = std::make_tuple(cube, level);

    cube->next_corners(&queue, 0);

    std::cout << queue.size() << std::endl;

    std::cout << "LEVEL 0\n\n" << cube->printable() << "LEVEL 1\n\n";

    for (int i = 0; i < queue.size(); ++i) {
        std::tie (cube, level) = queue.front();
        queue.pop();

        std::cout << cube->printable();

        hash.insert(cube);
        queue.push(cube);
    }

    std::cout << hash.size() << std::endl;

    for (int i = 0; i < hash.size(); ++i) {
        std::tie (cube, level) = queue.front();
        queue.pop();

        if (hash.contains(cube))
            std::cout << "si\n";
        else
            std::cout << "no\n";
    }

    // Aquí hay un segmentation fault 11 porque no está en el hashtable
    if (hash.contains(new Cube))
        std::cout << "NO DEBERIA ESTAR";
    else
        std::cout << "BIEN";

    return 0;
}
