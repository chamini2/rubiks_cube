#include "HashTable.hpp"
#include <math.h>

void array_swap(int &a, int &b);
void print_array(int *array, int n);
int rank(int n, int *array);
int aux_rank(int n, int *array, int *inverse);
int* inv_array(int* array, int size);
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

int *unrank(int n, int r) {
    int *array = new int[n];

    //  Arreglo identidad
    for (unsigned i = 0; i < n; ++i) {
        array[i] = i;
    }

    aux_unrank(n, r, array);

    return array;
}

void aux_unrank(int n, int r, int *array) {
    if (n > 0) {
        array_swap(array[n-1], array[r % n]);
        aux_unrank(n-1, floor(r/n), array);
    }
}

////////////////////////////////////////

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

////////////////////////////////////////

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (unsigned i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
}
