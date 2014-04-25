#include <math.h>
#include <iostream>
#include <fstream>
#include "extra.hpp"
#include "rank.hpp"

void print_array(int *array, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
}

int main(int argc, char const *argv[]) {
    int n = 8;
    int *array;

    array = unrank(n, 264539519);
    print_array(array, n);

    return 0;
}
