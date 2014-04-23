#include <math.h>
#include "rank.hpp"

void array_swap(int &a, int &b) {
    int temp;
    temp = b;
    b = a;
    a = temp;
}

int* inv_array(int* array, int size) {
    int *inverse = new int[size];

    for (unsigned i = 0; i < size; ++i) {
        inverse[array[i]] = i;
    }

    return inverse;
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

////////////////////////////////////////

int aux_rank(int n, int *array, int *inverse) {
    if (n == 1) {
        return 0;
    }

    int s = array[n-1];
    array_swap(array[n-1], array[inverse[n-1]]);
    array_swap(inverse[s], inverse[n-1]);

    return s + n * aux_rank(n-1, array, inverse);
}

int rank(int n, int *array) {
    int *inverse;
    int *aux = new int[n];
    int value, accum = 0;

    for (int i = 0; i < n; ++i) {
        aux[i] = cubie_to_pos(array[i]);
    }

    inverse = inv_array(aux, n);
    value = aux_rank(n, aux, inverse);

    delete[] inverse;
    delete[] aux;

    value *= pow(3,8);
    for (int i = 0; i < n; ++i) {
        accum = accum * 3 + cubie_to_orien(array[i]);
    }
    value += accum;

    return value;
}
