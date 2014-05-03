#include <cstdlib>
#include <ctime>
#include "../Set.hpp"

int main(int argc, char const *argv[]) {

    Cube *cube = new Cube, *new_cube;
    std::queue<Cube*> *queue;
    int size, which, loops = 3;

    if (argc > 1) {
        loops = atoi(argv[1]);
    }

    /* initialize random seed */
    srand (time(NULL));

    std::cout << cube->edges_to_string() << "\n -----------------------------------------------\n";

    for (int k = 0; k < loops; ++k) {
        queue = cube->succ();
        size = queue->size();

        which = rand() % 12;
        for (int i = 0; i < size; ++i) {
            new_cube = queue->front();
            queue->pop();

            if (i == which) {
                delete cube;
                cube = new_cube;
            } else {
                delete new_cube;
            }
        }
        std::cout << cube->edges_to_string() << " " << last_to_str(cube->get_last()) << "\n -----------------------------------------------\n";
    }

    delete cube;

    return 0;
}
