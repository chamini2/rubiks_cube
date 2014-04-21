#include "main.hpp"

int main(int argc, char const *argv[])
{
    std::queue<Cube*> queue;
    Cube* cube = new Cube;

    HashTable hash;

    cube->next_corners(&queue);

    std::cout << queue.size() << std::endl;

    std::cout << "LEVEL 0\n\n" << cube->printable() << "LEVEL 1\n\n";

    for (int i = 0; i < queue.size(); ++i) {
        cube = queue.front();
        queue.pop();

        std::cout << cube->printable();

        hash.insert(cube);
        queue.push(cube);
    }

    std::cout << hash.size() << std::endl;

    for (int i = 0; i < hash.size(); ++i) {
        cube = queue.front();

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
