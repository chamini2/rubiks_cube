#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../HashTable.hpp"

int main(int argc, char const *argv[]) {
    // int size;
    Cube *cube = new Cube;

    std::cout << cube->corners_to_string() <<"\n";
    cube->clock('l');
    std::cout << cube->corners_to_string() <<"\n";
    cube->clock('b');
    std::cout << cube->corners_to_string() <<"\n";
    // cube->clock('l');
    // cube->clock('l');
    cube->hundred('l');
    std::cout << cube->corners_to_string() <<"\n";


    if (cube->valid()) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    // Cube *suc;
    // std::queue<Cube*>* q;

    // for(unsigned i = 0; i < 8; ++i) {
    //     printf("%3d ", i);
    // }
    // std::cout << "\n";

    // std::cout << cube->corners_to_string() << cube->get_last() << "\n";

    // q = cube->succ();

    // size = q->size();

    // for(int i = 0; i < size-1; ++i) {
    //     suc = q->front();
    //     q->pop();
    // //    std::cout << suc->corners_to_string() << " " << suc->get_last() << "\n";
    // }


    // suc = q->front();
    // q->pop();
    // // std::cout << suc->corners_to_string() << " " << suc->get_last() << "\n";

    // suc->permutation_parity();

    // q = suc->succ();
    // size = q->size();

    // for(int i = 0; i < size; ++i) {
    //     suc = q->front();
    //     q->pop();
    //     std::cout << suc->corners_to_string() << " " << suc->get_last() << "\n";
    // }

}
