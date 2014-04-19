#include "main.hpp"

int main(int argc, char const *argv[])
{
    std::queue<Cube*> cubes;
    Cube* cube = new Cube;

    cube->next_corners(&cubes);

    std::cout << "LEVEL 0\n" << cube->to_string() << "LEVEL 1\n";

    for (int i = 0; i < cubes.size(); ++i) {
        cube = cubes.front();
        cubes.pop();
        std::cout << cube->to_string();
    }

    return 0;
}
