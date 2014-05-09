#include <iostream>
#include "../Cube.hpp"

int main(int argc, char const *argv[]) {

    Cube* cube = new Cube;
    std::queue<Cube*> *q = cube->succ();
    int size = q->size();

    std::cout << "size = " << size << "\n";
    std::cout << "test = " << (-1/3) << "\n";
    std::cout << "cube = " << cube->to_string() << "\n";

    for (int i = 0; i < size; ++i) {
        delete cube;
        cube = q->front();
        q->pop();
    }

    std::cout << "cube = " << cube->to_string() << "\n";
    cube->apply_inverse(cube->get_last());
    std::cout << "cube = " << cube->to_string() << "\n";

    return 0;
}
