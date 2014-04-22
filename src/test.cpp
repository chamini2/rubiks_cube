#include "HashTable.hpp"
#include <math.h>

void array_swap(int &a, int &b);
void print_array(int *array, int n);
void unrank(int n, int r, int *array);
int rank(int n, int *array);
int aux_rank(int n, int *array, int *inverse);
int* inv_array(int* array, int size);

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments: 2 expected." << std::endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int ranking = atoi(argv[2]);
    int *array = new int[n];
    int *array2;

    //  Arreglo identidad
    // for (unsigned i = 0; i < n; ++i) {
    //     array[i] = i;
    // }

    array[0] = 0;
    array[1] = 7;
    array[2] = 2;
    array[3] = 3;
    array[4] = 1;
    array[5] = 6;
    array[6] = 5;
    array[7] = 4;

    std::cout << rank(n, array) << std::endl;

    // std::cout << rank << ": ";
    // unrank(n , rank, array2);
    // print_array(array2, n);

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

///////////////////////////////////////////////////////////////////////////////

int rank(int n, int *array) {
    int *inverse = inv_array(array, n);

    return aux_rank(n, array, inverse);
}

int aux_rank(int n, int *array, int *inverse) {
    if (n == 1) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s+n*aux_rank(n-1, array, inverse);
}

///////////////////////////////////////////////////////////////////////////////

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (unsigned i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
}
