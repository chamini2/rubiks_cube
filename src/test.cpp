#include "HashTable.hpp"

int main(int argc, char const *argv[]) {
    Cube* cube = new Cube(false);
    Cube* a = new Cube(true);
    // std::queue<Cube*> q = cube->succ_corners();
    // a = q.front();

    if (cube->equals(a)) {
        std::cout << "BIEN";
    } else {
        std::cout << "MAL";
    }

}
