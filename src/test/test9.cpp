#include <stdlib.h>
#include "../rank.hpp"

int main(int argc, char const *argv[]) {
    int *array = new int[12];
    int i;

    // array[0]  = 8;
    // array[1]  = 103;
    // array[2]  = 109;
    // array[3]  = 101;
    // array[4]  = 2;
    // array[5]  = 111;
    // array[6]  = 7;
    // array[7]  = 6;
    // array[8]  = 0;
    // array[9]  = 4;
    // array[10] = 5;
    // array[11] = 10;

    array[0]  = 4;
    array[1]  = 201;
    array[2]  = 7;
    array[3]  = 209;
    array[4]  = 208;
    array[5]  = 210;
    array[6]  = 202;
    array[7]  = 200;
    array[8]  = 5;
    array[9]  = 203;
    array[10] = 6;
    array[11] = 211;

    for (int i = 0; i < 100; ++i) {
        std::cout << rand() % 6 << " ";
    }


    delete[] array;
    return 0;
}
