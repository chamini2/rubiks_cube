#include "../Set.hpp"

int main(int argc, char const *argv[]) {

    Cube *cube = new Cube, *new_cube;
    std::queue<Cube*> *queue;
    int size;

    std::cout << cube->edges_to_string() << "\n -------------------------------\n";

    queue = cube->succ();
    size = queue->size();

    for (int i = 0; i < size; ++i) {
        new_cube = queue->front();
        queue->pop();
        if (i == 7) {
            delete cube;
            cube = new_cube;
        } else {
            delete new_cube;
        }
    }

    std::cout << cube->edges_to_string() << " " << last_to_str(cube->get_last()) << "\n -------------------------------\n";
    queue = cube->succ();
    size = queue->size();

    for (int i = 0; i < size; ++i) {
        new_cube = queue->front();
        queue->pop();

        std::cout << new_cube->edges_to_string() << " " << last_to_str(new_cube->get_last()) << "\n";
        delete new_cube;
    }

    delete cube;

    return 0;
}
