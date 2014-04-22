#include "HashTable.hpp"
#include <math.h>

void array_swap(int &a, int &b);
void print_array(int *array, int n);
void unrank(int n, int r, int *array);

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments: 2 expected." << std::endl;
        return -1;
    }
    int n = atoi(argv[1]);
    int rank = atoi(argv[2]);
    int *array = new int[n];
    int *array2 = new int[n];

    //  Arreglo identidad
    for (unsigned i = 0; i < n; ++i) {
        array[i] = i;
        array2[i] = i;
    }

    std::cout << rank << ": ";
    unrank(n , rank, array2);
    print_array(array2, n);

    return 0;
}


void array_swap(int &a, int &b) {
    int temp;
    temp = b;
    b = a;
    a = temp;
}

void print_array(int *array, int n) {
    for (unsigned i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void unrank(int n, int r, int *array) {
    if (n > 0) {
        array_swap(array[n-1], array[r % n]);
        unrank(n-1, floor(r/n), array);
    }
}
