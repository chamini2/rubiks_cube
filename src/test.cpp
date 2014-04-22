#include "HashTable.hpp"
#include <math.h>

void array_swap(int &a, int &b);
void print_array(int *array, int n);
int* unrank(int n, int r);

int main(int argc, char const *argv[]) {
    int n;
    int rank;
    int *array;

    if (argc == 3) {
        n = atoi(argv[1]);
        rank = atoi(argv[2]);
    } else if (argc == 2) {
        n = atoi(argv[1]);
        rank = factorial(n) - 1;
    } else {
        n = 8;
        rank = factorial(n) - 1;
    }

    std::cout << "n: (" << n << ") rank: (" << rank << ")\n";

    for (int i = 0; i <= rank; ++i) {
        std::cout << i << ": ";
        array = unrank(n , i);
        print_array(array, n);
        delete[] array;
    }

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

////////////////////////////////////////

void aux_unrank(int n, int r, int *array) {
    if (n > 0) {
        array_swap(array[n-1], array[r % n]);
        aux_unrank(n-1, floor(r/n), array);
    }
}

int *unrank(int n, int r) {
    int *array = new int[n];

    //  Arreglo identidad
    for (unsigned i = 0; i < n; ++i) {
        array[i] = i;
    }

    aux_unrank(n, r, array);

    return array;
}
